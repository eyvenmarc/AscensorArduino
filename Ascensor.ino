
//******* LIBRERIAS ********
#include <Temporizador.h> // Incluimos una librería de temporización

//******* CONSTANTES *******
const int IxP0 = 2; // Planta 0 del optoacoplador detector de plantas. Pin 2
const int OpEnaMotor = 6;  // Control del Motor Enabled. Pin 6
const int OxIn1Motor = 7; // Control del Motor IN1. Pin 7
const int OxIn2Motor = 8; // Control del Motor IN2. Pin 8
const int OxLuzCabina = 9; // Luz de la cabina del ascensor. Pin 9
const int IxSubir = 11; // Pulsador de movimiento manual de subida del ascensor. Pin 11
const int IxBajar = 12; // Pulsador de movimiento manual de bajada del ascensor. Pin 12
const int IaPresencia = 14; // Sensor de presencia. Indica si hay alguien en la cabina del ascensor. Pin 14
const int ACTIVADO = LOW; // Indica si la entrada se activa a nivel alto o bajo
const int PARAR = 0; const int SUBIR = 1; const int BAJAR = 2; // Indica la acción del motor de ascensor
const int PLANTA_OK = 1; // El ascensor ha llegado a la planta indicada 
const int PLANTA_FALLO = -1;  // El ascensor no ha llegado a la planta indicada
const int TIEMPOS[] = {100, 150, 100, 150, 100, 1200}; // Alarma. Tiempo en milisegundos de Encendido/Apagado luz cabina

//******* ESTRUCTURAS *******
struct PuertoCom {  // Creamos una estructura para el puerto serie
  bool Disponible;  // Si existen caracteres disponibles en el puerto serie (Terminador '\n')
  String Dato;      // Dato del puerto serie
};

// ***** VARIABLES GLOBALES *****
Temporizador tmrProceso;  // Tiempo máximo que puede trascurrir en el movimiento del ascensor de una planta a otra
Temporizador tmrEsperaAscensor; // Tiempo de espera desde que el ascensor está en planta hasta la subida de persona
Temporizador tmrLecturaSensor; // Tiempo que transcurre desde la no presencia del sensor hasta el apagado de luz
Temporizador tmrParpadeoLuz; // Tiempo que transcurre entre parapadelo de la luz de la cabina
PuertoCom Serie;  // Creamos la variable Serie con la estructura PuertoCom
byte gbytVelocidad = 255;  // Velocidad del motor por defecto
int gintProximidadOK = 50; // Valor mínimo de proximidad de existencia de un objeto en la cabina

// ******** CONFIGURACIÓN E INICIO ********
void setup() {
	Serial.begin(9600); // Se inicia el puerto serie a 9600 baudios
  pinMode(IxP0,INPUT); // Optoacoplador Planta 0. Pin 2. Configuracion de Pin como Entrada
  pinMode(IxP0 + 1,INPUT); // Optoacoplador Planta 1. Pin 3. Configuracion de Pin como Entrada
  pinMode(IxP0 + 2,INPUT); // Optoacoplador Planta 2. Pin 4. Configuracion de Pin como Entrada
  pinMode(IxP0 + 3,INPUT); // Optoacoplador Planta 3. Pin 5. Configuracion de Pin como Entrada
  pinMode(OpEnaMotor,OUTPUT); // Control del Motor Enabled. Pin 6. Configuracion de Pin como Salida
  pinMode(OxIn1Motor,OUTPUT); // Control del Motor IN1. pin 7. Configuracion de Pin como Salida
  pinMode(OxIn2Motor,OUTPUT); // Control del Motor IN2. pin 8. Configuracion de Pin como Salida
  pinMode(OxLuzCabina,OUTPUT); // Led de la cabina del ascensor. Pin 9 Configuracion de Pin como Salida
  pinMode(IxSubir,INPUT); // Pulsador manual de subida del ascensor. Pin 11. Configuracion de Pin como Entrada
  pinMode(IxBajar,INPUT); // Pulsador manual de bajada del ascensor. Pin 12. Configuracion de Pin como Entrada
  pinMode(LED_BUILTIN,OUTPUT); // Declaramos el pin 13 (Led placa) como salida para posibles pruebas
  pinMode(IaPresencia,INPUT); // Sensor de presencia en la cabina del ascensor. Pin 14/A0. Configuracion de Pin como Entrada
  
  analogWrite(OpEnaMotor,0); // Coloca la velocidad a 0
  digitalWrite(OxIn1Motor,LOW); // Desactiva el Motor pin 1 + pin 2 a 0
  digitalWrite(OxIn2Motor,LOW); // Desactiva el Motor pin 1 + pin 2 a 0
}

// ******** PROGRAMA ********
void loop() {
  static int intProcesoPri; // Número del proceso que se encuentra el desplazamiento del ascensor
  static int intProcesoLuz; // Número de proceso que se encuentra la activación por presencia de la luz de la cabina
  static int intProcesoAla; // Número de proceso que se encuentra la activación de la luz de la cabina por emergencia
  static int intPL; // Número de planta que se indica desde el puerto serie
 	static int intPer; // Indica si debe existir persona en la cabina desde el puerto serie
  static int intMotorManual; // Estado que se encuentra el motor en modo manual Parado/Subir/Bajar
  static int intContador; // Contador de acciones de Encendido/Apagado en parapadeo led en emergencia
  int intRespuesta = 0; // Respuesta de las funciones

  DatoSerie();  // Examina si existen datos en el puerto serie y almacena los bytes hasta final de mensaje '\n' asc(10)
	
  // ********** DESPLAZA EL ASCENSOR A LA PLANTA INDICADA **********
  switch (intProcesoPri) { 
    case 0: { // Proceso 0. *** Verifica si existe mensaje de desplazar el ascensor a una planta ***
      if (Serie.Disponible) { // Si hay un dato disponible en el puerto serie
        if (Serie.Dato.length() >= 3) { // Si la longitud del dato serie es >= a 3 caracteres
          if (Serie.Dato.substring(0,1) == "P") { // Si el primer caracter es una 'P'
            Serial.print("--- "); Serial.print(Serie.Dato); Serial.println(" ---"); // *** BORRAR ***
            String strPL = Serie.Dato.substring(1,2); // Almacena en strPL el caracter del número de planta
            String strPer = Serie.Dato.substring(2,3); // Almacena en strPer el caracter de si existe persona en cabina
            intPL = strPL.toInt(); // Convierte el caracter del número de planta a entero 'int'
            intPer = strPer.toInt(); // Convierte el caracter del número de persona en cabina a entero 'int'
            if ((intPL >= 0 && intPL <= 3) && (intPer == 0 || intPer == 1)) { // Si Planta entre 0 y 3 y Persona en cabina entre 0 o 1
              if (intPL == 0) { // Si hay que ir a la planta 0
                intProcesoPri = 1; // Continua con el siguiente proceso. Planta 0
              }
              else if (intPL >= 1 && intPL <= 3) { // Si hay que ir de la planta 1 a la 3
                int intPlanta = PlantaActual(); // Almacena la planta en que se encuentra el ascensor
               if (intPlanta >= 0 && intPlanta <= 3) { // Si el asensor se encuentra entre la planta 0 y 3
                  intProcesoPri = 1;  // Continua con el siguiente proceso. Verificar persona
                }
                else { // Si el asensor no se encuentra entre la planta 0 y 3
                Serial.println("p-"); // Envía el mensaje de no saber en que planta se encuentra
                }
              }
            }
          }
        }
      }
      break;
    } 
    case 1: { // Proceso 1. Comprueba si el ascensor debe desplazarse con o sin persona
      int intLecturaSensor = analogRead(IaPresencia); // Almacena el valor del sensor en intLecturaSensor
      Serial.print("Presencia: "); Serial.println(intLecturaSensor);
      if (intPer == 0 ) { // Si no debe haber persona en el ascensor
        if (intLecturaSensor >= gintProximidadOK) { // Si el valor del sensor es igual o mayor de lo establecido. Hay presencia
          Serial.println("pp"); // Envía mensaje que en el ascensor hay persona y debe ir vacío
          intProcesoPri = 0; // Vuelve al proceso 0
        }
        else { // Si el valor del sensor es menor de lo establecido. No hay presencia
          intProcesoPri = 5; // Continua con el proceso 5. Movimiento ascensor
        }
      }
      else if (intPer == 1) {  // Si debe haber persona en el ascensor
        if (intLecturaSensor < gintProximidadOK) { // Si el valor del sensor es menor de lo establecido. No hay presencia
          tmrEsperaAscensor.temporizar(0,0,0,3,500); // Inicia el temporizador para dejar tiempo a que suban al ascensor
          digitalWrite(OxLuzCabina, HIGH); // Enciende la luz de la cabina 
          intProcesoPri = 2; // Continua con el siguiente proceso. Espera persona
        }
        else { // Si el valor del sensor es mayor o igual de lo establecido. Hay presencia
         intProcesoPri = 5; // Continua con el proceso 5. Movimiento ascensor
        }
      }
      break;
    }  
    case 2: { // Proceso 2. Espera a que pase la persona a la cabina del ascensor
      int intLecturaSensor = analogRead(IaPresencia); // Almacena el valor del sensor en intLecturaSensor
      if (intLecturaSensor >= gintProximidadOK) { // Si el valor del sensor es igual o mayor de lo establecido. Hay presencia
        intProcesoPri = 3; // Continua con el siguiente proceso.
      }
      else if (tmrEsperaAscensor.completado()) { // Si ha expirado el tiempo de espera
        Serial.println("pv"); // Envía mensaje que el ascensor está vacío y debe ir con persona
        digitalWrite(OxLuzCabina, LOW); // Apaga la luz de la cabina 
        intProcesoPri = 0; // Vuelve al proceso 0
      }
      break;
    }
    case 3: { // Proceso 3. Espera a que se coloque la persona en la cabina del ascensor
      tmrEsperaAscensor.temporizar(0,0,0,2,0); // Inicia el temporizador para dejar tiempo a que se coloque en el ascensor
      intProcesoPri = 4; // Continua con el siguiente proceso.
      break;
    }
    case 4: { // Proceso 4. Si ha expirado el tiempo de espera
      if (tmrEsperaAscensor.completado()) { // Si ha expirado el tiempo de espera
          intProcesoPri = 5; // Continua con el proceso 5. Movimiento ascensor
      }
      break;
    }
    case 5: { // Proceso 5. *** Envía el ascensor a la planta indicada ***
      int intRespuesta = 0;
      intRespuesta = Planta(intPL); // LLama a la función de colocar el ascensor en la planta indicada
      if (intRespuesta >=10 && intRespuesta <= 13) { // Si la función devuelve entre 10 y 13 indica la planta donde se encuentra
        Serial.print ("p"); Serial.println (intRespuesta - 10); // Envía el número de planta donde se encuentra el ascensor
      }
      if (intRespuesta == PLANTA_OK) { // Si la respuesta es OK el ascensor está en la planta indicada
          intProcesoPri = 6; // Continua al siguiente proceso. Cabina vacia
      }
      else if (intRespuesta == PLANTA_FALLO) { // Si la respuesta es Fallo existe una incidencia en el ascensor
        Serial.println ("pe"); // Envía el mensaje de planta error
        intProcesoPri = 0; // Vuelve al proceso 0
      }
      break;
    }
    case 6: { // Proceso 6. Espera a que la cabina se quede vacia
      int intLecturaSensor = analogRead(IaPresencia); // Almacena el valor del sensor en intLecturaSensor
      if (intLecturaSensor < gintProximidadOK) { // Si el valor del sensor es menor de lo establecido. No hay presencia
        Serial.println ("pk"); // Envía el mensaje de proceso terminado correctamente
        intProcesoPri = 0; // Vuelve al proceso 0
      }
      break;
    }
  }

  // ******** ENCENDIDO/APAGAGADO DE LA LUZ DE LA CABINA **********
  switch (intProcesoLuz) {
    case 0: { // Proceso 0. Examina el valor del sensor de proximidad y enciende la cabina
      int intLecturaSensor = analogRead(IaPresencia); // Almacena el valor del sensor en intLecturaSensor
      if (intLecturaSensor >= gintProximidadOK) { // Si el valor del sensor es igual o mayor de lo establecido
        digitalWrite(OxLuzCabina, HIGH); // Enciende la luz de la cabina 
        intProcesoLuz = 1; // Continua con el siguienta proceso
      }
      break;
    }
    case 1: { // Proceso 1. Examina el valor del sensor de proximidad y inicia el temporizador
      int intLecturaSensor = analogRead(IaPresencia); // Almacena el valor del sensor en intLecturaSensor
      if (intLecturaSensor < gintProximidadOK) { // Si el valor del sensor es menor de lo establecido
        tmrLecturaSensor.temporizar(0, 0, 0, 1, 500); // Inicia el temporizador para apagar la luz
        intProcesoLuz = 2; // Continua con el siguienta proceso
      }
      break;
    }
    case 2: { // Proceso 2. Espera a que expire el tiempo para apagar la luz de la cabina
      if (tmrLecturaSensor.completado()) { // Si ha expirado el tiempo de espera
          digitalWrite(OxLuzCabina, LOW); // Apaga la luz de la cabina
          intProcesoLuz = 0; // Vuelve al proceso 0
        break;
      }
    }
  }

  // ******** CONSULTA LA PLANTA DONDE SE ENCUENTRA EL ASCENSOR ********
  if (Serie.Disponible) { // Si hay un dato disponible en el puerto serie
    if (Serie.Dato.length() >= 2) { // Si la longitud del dato serie es >= a 2 caracteres
      if (Serie.Dato.substring(0, 2) == "P?") { // Si el dato es 'P?'
        int intPlanta = PlantaActual();
        Serial.print("p"); // Envía la primera letra del mensaje
        if (intPlanta >= 0 && intPlanta <= 3) {
          Serial.println(intPlanta); // Envía el mensaje del número de planta
        }
        else {
          Serial.println("-"); // Envía el mensaje de no saber en que planta se encuentra
        }
      }
    }
  }
  
  // ******** CONSULTA DE PRESENCIA DE PERSONA EN CABINA DEL ASCENSOR ********
  if (Serie.Disponible) { // Si hay un dato disponible en el puerto serie
    if (Serie.Dato.length() >= 2) { // Si la longitud del dato serie es >= a 2 caracteres
      if (Serie.Dato.substring(0, 2) == "C?") { // Si el dato es 'C?'
        int intLecturaSensor = analogRead(IaPresencia); // Almacena el valor del sensor en intLecturaSensor
        if (intLecturaSensor >= gintProximidadOK) { // Si el valor del sensor es igual o mayor de lo establecido
          Serial.println("c1"); // Envía el mensaje de presencia de persona en cabina
        }
        else {
          Serial.println("c0");// Envía el mensaje de no hay presencia de persona en cabina
        }
      }
    }
  }
  
  // ********* ALARMA POR INCENDIO *********
  // Verifica si existe mensaje de alarma de incendio
  if (Serie.Disponible) { // Si hay un dato disponible en el puerto serie
    if (Serie.Dato.length() >= 2) { // Si la longitud del dato serie es >= a 2 caracteres
      if (Serie.Dato.substring(0,2) == "A1") { // Si el dato es "A1" activa Alarma por incendio
        intProcesoAla = 1; // Activa el proceso de parpadeo de emergencia de la luz de cabina
      }
      else if (Serie.Dato.substring(0,2) == "A0") { // Si el dato es "A0" desactiva Alarma por incendio
        digitalWrite(OxLuzCabina, LOW); // Apaga la luz de la cabina
        intProcesoPri = 0; // Activa el proceso de movimiento del ascensor
        intProcesoLuz = 0; // Activa el proceso de encendido de luz de cabina
        intProcesoAla = 0; // Desctiva el proceso de parpadeo de emergencia de la luz de cabina
      }
    }
  }
  switch (intProcesoAla) { 
    case 1: { // Si el ascensor está en movimiento, espera a que el proceso de movimiento del ascensor termine
      if (intProcesoPri == 0) { // Si el proceso de movimiento del ascensor está parado
        intProcesoPri = -1; // Desactiva el proceso de movimiento del ascensor
        intProcesoLuz = -1; // Desactiva el proceso de encendido de luz de cabina
        intProcesoAla = 2; // Continua con el siguiente proceso
      }
      break;
    }
    case 2: { // Enciendido/Apagado luz de cabina
      int intAcciones = sizeof(TIEMPOS) / sizeof(TIEMPOS[0]); // Almacena el número de datos del arreglo (acciones encendidos/apagados)
      if (intContador >= intAcciones) { // Si el contador es mayor al número de datos del arreglo (acciones)
        intContador = 0; // Coloca el contador a 0
      }
      int intTiempo = TIEMPOS[intContador]; // Almacena el tiempo en milisegundos del arreglo para el temporizador
      tmrParpadeoLuz.temporizar(0,0,0,0,intTiempo); // Inicia el temporizador
      bool blnLuz = digitalRead(OxLuzCabina); // Lee el estado actual de luz de la cabina
      digitalWrite(OxLuzCabina, !blnLuz); // Se invierte el estado de la luz de la cabina
      intContador ++; // Se incrementa el contador
      intProcesoAla = 3; // Continua con el siguiente proceso
      break;
    }
    case 3: { // Tiempo de espera
      if (tmrParpadeoLuz.completado()) { // Si ha expirado el tiempo
         intProcesoAla = 2; // Vuelve al proceso anterior
      }
      break;
    }
  }

    // ********* CONFIGURACIÓN DEL VALOR MÍNIMO DEL SENSOR DE PROXIMIDAD **********
  if (Serie.Disponible) { // Si hay un dato disponible en el puerto serie
    if (Serie.Dato.length() >= 2) { // Si la longitud del dato serie es >= a 2 caracteres
      if (Serie.Dato.substring(0, 2) == "L?") { // Si el dato es 'L?'
        Serial.print("l"); Serial.println(analogRead(IaPresencia)); // Devuelve el valor actual del sensor de proximidad
      }
      else if (Serie.Dato.substring(0, 1) == "L") { // Si el dato es 'L'  
        int intProximidadOK; // Valor de 0 a 4096
        intProximidadOK = Serie.Dato.substring(1).toInt();
        if (intProximidadOK > 0) { // Si es un número mayor de 0 almacena el valor mínimo del sensor de proximidad
          gintProximidadOK = intProximidadOK; // Almacena el valor mínimo del sensor de proximidad
          Serial.print("L"); Serial.println(gintProximidadOK); // Devuelve el valor mínimo del sensor de proximidad
        }
      }
    }
  }
  
  // ********* CONFIGURACIÓN DE LA VELOCIDAD DEL MOTOR **********
  if (Serie.Disponible) { // Si hay un dato disponible en el puerto serie
    if(Serie.Dato.substring(0,1) == "V") {  // Si el primer caracter del dato del puerto serie es igual a 'V' modifica la velocidad del motor
      byte bytVelocidad; // Velocidad de 1 a 255
      bytVelocidad = Serie.Dato.substring(1).toInt();
      if (bytVelocidad > 0) { // Si es un número mayor de 0 almacena la velocidad
        gbytVelocidad = bytVelocidad; // Almacena la velocidad del motor 
      }
      Serial.print("V"); Serial.println(gbytVelocidad); // Devuelve la velocidad almacenada
    }
  }

  // ********* MOVIMIENTO MANUAL DEL MOTOR DEL ASCENSOR *********
  if (intProcesoPri <= 0 && intMotorManual == PARAR ) { // Si no está iniciado el ProcesoPri y no se han pulsado los botones subir o bajar
    if (digitalRead(IxSubir) & digitalRead(IxP0 + 3) != ACTIVADO) { // Si se ha pulsado el botón subir y no ha llegado al opto 3
      Motor(SUBIR); // Activa la Subida en el motor del ascensor
      intMotorManual = SUBIR; // Almacena se ha pulsado el botón manual de Subir
    }
    else if (digitalRead(IxBajar) & digitalRead(IxP0) != ACTIVADO) { // Si se ha pulsado el botón bajar y no ha llegado al opto 0
      Motor(BAJAR); // Activa la Bajada en el motor del ascensor
      intMotorManual = BAJAR; // Almacena se ha pulsado el botón manual de Bajar
    }
  }
  if (intMotorManual != PARAR) {  // Si se ha pulsado algún botón anteriormente de subir o bajar
      // Si el intProcesoPri ha comenzado o si no se han pulsado los botones subir y bajar o
      // si se activa el opto 3 subiendo o se activa el opto 0 bajando se para el ascensor 
    if (intProcesoPri > 0 || (!digitalRead(IxSubir) && !digitalRead(IxBajar)) ||
        (intMotorManual == SUBIR & digitalRead(IxP0 + 3) == ACTIVADO) || (intMotorManual == BAJAR & digitalRead(IxP0) == ACTIVADO)) {
      Motor(PARAR); // Para el motor del ascensor
      intMotorManual = PARAR; // Almacena en la variable motor parado
    }
  }
}

// ************** FUNCIONES **************
//******** DESPLAZA EL ASCENSOR A UNA PLANTA *********
int Planta(int intPlanta) {
  static int intProcesoPla; // Número del proceso que se encuentra el desplazamiento del ascensor a una planta
  static bool blnSubir; // Indica si tiene que subir o bajar el ascensor
  static int intUltimaPlanta = 4; // Almacena la última planta detectada
  int intEstado = 0; // Variable de retorno de la función Planta 
 
  switch (intProcesoPla) {
    case 0: { // Proceso 0. *** Determina si está en la planta hay que subir o bajar ***
      int intPlantaActual = 0; // Crea e inicializa la variable a 0
      intEstado = 0; // Inicializa la variable a 0
      Serial.println("intProcesoPla 0");  // *** BORRAR***
      intPlantaActual = PlantaActual(); // Examina la planta donde se encuentra el ascensor
      if (intPlantaActual == intPlanta) { // Si la planta actual es igual a la planta designada
        intEstado = PLANTA_OK; // La función devuelve, Ascensor en planta
        break;
      }
      else if (intPlantaActual > intPlanta) { // Si la planta actual es mayor que la planta asignada
        blnSubir = false; // Hay que bajar
        intProcesoPla = 1; // Continua al siguiente proceso 
      }
      else if (intPlantaActual < intPlanta) { // Si la planta actual es menor que la planta asignada
        blnSubir = true; // Hay que subir
        intProcesoPla = 1; // Continua al siguiente proceso 
      }
      Serial.print("Planta actual: "); Serial.println(intPlantaActual); // *** BORRAR ***
      Serial.print("Subir: "); Serial.println(blnSubir); // *** BORRAR ***
      Serial.print("Opto: "); // *** BORRAR ***
      Serial.print(digitalRead(IxP0 + 0)); Serial.print(digitalRead(IxP0 + 1)); // *** BORRAR ***
      Serial.print(digitalRead(IxP0 + 2)); Serial.println(digitalRead(IxP0 + 3)); // *** BORRAR ***
      break;
    } 
    case 1: { // Proceso 1. *** Activa el temporizador de tiempo límite de movimiento del motor *** 
      Serial.println("intProcesoPla 1"); // *** BORRAR ***
      Motor(PARAR); // Para el motor del ascensor
      int intTiempo = abs(intPlanta - PlantaActual()) * 4; // Se asignan 4 segundos por planta
      Serial.print("Diferencia plantas: "); Serial.println(intTiempo); // *** BORRAR ***
      tmrProceso.temporizar(0,0,0,intTiempo,0); // Inicia el temporizador para realizar la maniobra de colocarse en la planta
      intProcesoPla = 2; // Continua al siguiente proceso 
      break;
    }
    case 2: { // Proceso 2. *** Activa el motor para subir o bajar ***
      if (blnSubir) { // Si hay que subir
        Motor(SUBIR); // Sube el motor del ascensor
      }
      else { // Si hay que bajar
        Motor(BAJAR); // Baja el motor del ascensor
      }
      Serial.println("intProcesoPla 2"); // *** BORRAR ***
      Serial.print("Subir: "); Serial.println(blnSubir); // *** BORRAR ***
      Serial.println("Temporizador movimiento ascensor"); // *** BORRAR ***
      Serial.println("intProcesoPla 3"); // *** BORRAR ***
      intProcesoPla = 3; // Continua al siguiente proceso 
      break;
    }    
    case 3: { // Proceso 3. *** Comprueba si ha llegado a la planta o ha expirado el tiempo de maniobra ***
      int intPlantaActual = 0; //Crea e inicializa la variable a 0
      if (digitalRead(IxP0 + intPlanta) == ACTIVADO) {  // Si ha llegado a la planta asignada, para el Motor
        Motor(PARAR); // Para el motor del ascensor
        intProcesoPla = 4; // Continua al siguiente proceso 
      }
      else if (tmrProceso.completado()) { // Si ha expirado el tiempo de maniobra de colocarse en planta, para el motor
        Motor(PARAR); // Para el motor del ascensor
        intEstado = PLANTA_FALLO; // La función devuelve que el ascensor no ha llegado a la planta indicada
        intProcesoPla = 0; // Vuelve al proceso 0 
      }
      intPlantaActual = PlantaActual(); // Comprueba en que planta se encuentra el ascensor
      if (intUltimaPlanta != intPlantaActual) { // Si la última planta almacenada es distinta a la actual
        if (intPlantaActual >= 0 && intPlantaActual <= 3) { // Si la planta es entre 0 y 3
          intEstado = intPlantaActual + 10; // La función devuelve el número de planta + 10
          intUltimaPlanta = intPlantaActual; // Almacena el número de planta actual
        }
      }
      break;
    }
    case 4: { // Proceso 4. *** Da tiempo a devolver el número de planta antes de finalizar ***
      // Serial.println("intProcesoPla 4"); // *** BORRAR ***
      intEstado = PLANTA_OK; // La función devuelve ascensor en planta
      intProcesoPla = 0; // Vuelve al proceso 0 
      break;
    }
  }
  return intEstado; // Variable de devolución de función
}

// ****** MOVIMIENTO DE SUBIDA/BAJADA Y PARADA MOTOR ******
void Motor(int Accion) { // Acción del motor
  if (Accion == PARAR) { // Parada del motor
    analogWrite(OpEnaMotor,0); // Coloca la velocidad a 0
    digitalWrite(OxIn1Motor,LOW); // Coloca a 0 el pin 1 del Motor
    digitalWrite(OxIn2Motor,LOW); // Coloca a 0 el pin 2 del Motor
  }
  else if (Accion == SUBIR) { // Subida del motor
    analogWrite(OpEnaMotor,gbytVelocidad); // Envía frecuencia por el pin Enabled del Motor
    digitalWrite(OxIn1Motor,LOW); // Coloca a 0 el pin 1 del Motor
    digitalWrite(OxIn2Motor,HIGH); // Coloca a 1 el pin 2 del Motor
  }
  else if (Accion == BAJAR) { // Bajada del motor
    analogWrite(OpEnaMotor,gbytVelocidad); // Envía frecuencia por el pin Enabled del Motor
    digitalWrite(OxIn1Motor,HIGH); // Coloca a 1 el pin 1 del Motor
    digitalWrite(OxIn2Motor,LOW); // Coloca a 0 el pin 2 del Motor
  }
}

// ********* NOTIFICA LA PLANTA DONDE SE ENCUENTRA EL ASCENSOR *********
int PlantaActual() {
  int intPlanta = 0;

  do {  // Examina desde la planta 0 a la 3 para saber donde se encuentra el ascensor
    if (digitalRead(IxP0 + intPlanta) == ACTIVADO) { // Cuando encuentra la planta sale del bucle y 
      break;                                         // queda almacenada la planta donde se encuentra el ascensor
    }
    intPlanta ++; // Incrementa en 1 la planta
  }
  while (intPlanta < 4); // Si la planta actual es mayor a 3 sale del bucle. No hay ningún optoacoplador activado  
  return intPlanta; // Variable de devolución de función
}

// *********** ALMACENA LOS BYTES DEL PUERTO SERIE ***********
void DatoSerie() {
	static int intProcesoSer;

	switch (intProcesoSer) { 
    case 0: // Si esta en el proceso 0
       while (Serial.available()) { // Si existe algún caracter en el puerto serie
        char chrCaracter = Serial.read(); // Lee un caracter del puerto serie
        if (chrCaracter == '\n') {  // Si el caracter es un avance de línea asc(10)
          Serie.Disponible = true;  // Comunica que existe un dato en el puerto serie
          intProcesoSer = 1; // Sale del proceso 0 de leer datos del puerto serie y continua con el siguiente en el próximo ciclo
        }
        else {  // Si no es un caracter de avance de línea asc(10)
		      Serie.Dato.concat(chrCaracter); // Concatena los caracteres del puerto serie en la variable
        }
      }
      break;
    case 1: // Si está en el proceso 1. Los datos del puerto serie permanecen en las variables sólo un ciclo
      Serie.Disponible = false; // Comunica que ya no hay dato en el puerto serie
      Serie.Dato = "";  // Elimina los caracteres almacenados del puerto serie
      intProcesoSer = 0; // Vuelve al proceso 0
      break;
  } 
}
