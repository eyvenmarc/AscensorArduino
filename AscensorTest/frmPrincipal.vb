Public Class frmPrincipal
		Private Sub frmPrincipal_Load(sender As Object, e As EventArgs) Handles MyBase.Load
				'Para tener acceso a los controles del formulario desde un hilo distinto. (Evento DataReceived del puerto COM)
				CheckForIllegalCrossThreadCalls = False

				'Busca y añade todos los puertos existentes del PC en el ComboBox
				For Each Puertos As String In My.Computer.Ports.SerialPortNames
						cboPuertos.Items.Add(Puertos)
				Next
		End Sub
		Private Sub btnAceptarCOM_Click(sender As Object, e As EventArgs) Handles btnAceptarCOM.Click
				'Si existe algún puerto
				If cboPuertos.Text <> "" Then
						Try
								'Abre el puerto con el puerto seleccionado
								comArduino.PortName = cboPuertos.Text
								comArduino.Open()
								'Envía mensaje de información de la planta actual
								comArduino.WriteLine("P?")
								'Habilita los restantes controles del formulario
								Controles(True)
						Catch ex As Exception
								MessageBox.Show(ex.Message)
						End Try
				'Si no existe ningún puerto
				Else
						MessageBox.Show("No se ha selecionado ningún puerto COM válido")
				End If
		End Sub
		Private Sub btnPlanta0_Click(sender As Object, e As EventArgs) Handles btnPlanta0.Click
				Dim strMensaje As String = "P0" & chkPersona.Tag

				'Envia mensaje ir a Planta 0
				Enviar(strMensaje)
				lblMensajes.Text = ""
		End Sub
		Private Sub btnPlanta1_Click(sender As Object, e As EventArgs) Handles btnPlanta1.Click
				Dim strMensaje As String = "P1" & chkPersona.Tag

				'Envia mensaje ir a Planta 1
				Enviar(strMensaje)
				lblMensajes.Text = ""
		End Sub
		Private Sub btnPlanta2_Click(sender As Object, e As EventArgs) Handles btnPlanta2.Click
				Dim strMensaje As String = "P2" & chkPersona.Tag

				'Envia mensaje ir a Planta 2
				Enviar(strMensaje)
				lblMensajes.Text = ""
		End Sub
		Private Sub btnPlanta3_Click(sender As Object, e As EventArgs) Handles btnPlanta3.Click
				Dim strMensaje As String = "P3" & chkPersona.Tag

				'Envia mensaje ir a Planta 3
				Enviar(strMensaje)
				lblMensajes.Text = ""
		End Sub
		Private Sub btnConsultarSensor_Click(sender As Object, e As EventArgs) Handles btnConsultarSensor.Click
				'Envía mensaje de información del valor del sensor de proximidad
				Enviar("L?")
		End Sub
		Private Sub btnCambiarLimite_Click(sender As Object, e As EventArgs) Handles btnCambiarLimite.Click
				'Envía mensaje con el valor del límite de activación del sensor de proximidad
				Enviar("L" & txtLimite.Text)
				txtLimite.Text = ""
		End Sub
		Private Sub btnAlarma_Click(sender As Object, e As EventArgs) Handles btnAlarma.Click
				'Envía mensaje de Activar/Desactivar la alarma de incendio 
				If btnAlarma.Text = "Activar Alarma" Then
						Enviar("A1")
						btnAlarma.Text = "Desactivar Alarma"
				Else
						Enviar("A0")
						btnAlarma.Text = "Activar Alarma"
				End If
		End Sub
		Private Sub chkPersona_CheckedChanged(sender As Object, e As EventArgs) Handles chkPersona.CheckedChanged
				'Almacena en la propiedad Tag, 1 si está activado o 0 si está desactivado
				If chkPersona.Checked Then
						chkPersona.Tag = 1
				Else
						chkPersona.Tag = 0
				End If
		End Sub
		Private Sub comArduino_DataReceived(sender As Object, e As IO.Ports.SerialDataReceivedEventArgs) Handles comArduino.DataReceived
				Dim intCaracter As Integer
				Static strCadena As String

				Try
						'Si no hay ningún byte en el buffer del puerto no continua
						If comArduino.BytesToRead <= 0 Then Exit Sub

						'Mientras existan bytes en buffer del puerto
						Do While comArduino.BytesToRead > 0
								intCaracter = comArduino.ReadChar()
								'Si el caracter es Avance de línea (lf) ó (10 en ASCII)
								If intCaracter = 10 Then
										'El mensaje se ha completado
										Recibir(strCadena)
										strCadena = ""
								Else
										'Añade caracteres al mensaje hasta que se complete
										strCadena += Chr(intCaracter)
								End If
						Loop
				Catch ex As Exception
						MessageBox.Show(ex.InnerException.Message)
						Controles(False)
				End Try
		End Sub
		Private Sub Enviar(ByVal Mensaje As String)
				Try
						'Envía el mensaje por el puerto serie
						comArduino.WriteLine(Mensaje)
				Catch ex As Exception
						MessageBox.Show(ex.InnerException.Message)
						Controles(False)
				End Try
		End Sub
		Private Sub Recibir(ByVal Mensaje As String)
				Dim strChar1 As String
				Dim strChar2 As String

				'Si la longitud del mensaje es menor de 2 caracteres no continua
				If Len(Mensaje) < 2 Then Exit Sub
				strChar1 = Mid(Mensaje, 1, 1)
				strChar2 = Mid(Mensaje, 2, 1)

				'Si el primer caracter del mensaje comienza por 'p'
				If strChar1 = "p" Then
						'Examina el segundo caracter del mensaje y visualiza las incidencias en el despalzamiento del ascensor
						Select Case strChar2
								Case "k"
										lblMensajes.Text = "Desplazamiento del ascensor terminado"
								Case "e"
										lblMensajes.Text = "El ascenssor no se ha deplazado correctamente"
								Case "v"
										lblMensajes.Text = "La cabina del ascensor debe ir con persona"
								Case "p"
										lblMensajes.Text = "La cabina del ascensor debe estar vacia"
								Case "0"
										lblPlanta.Text = "0"
								Case "1"
										lblPlanta.Text = "1"
								Case "2"
										lblPlanta.Text = "2"
								Case "3"
										lblPlanta.Text = "3"
								Case "-"
										lblPlanta.Text = "-"
										lblMensajes.Text = "Planta indefinida"
						End Select
				End If
				'Si el primer caracter del mensaje comienza por 'c'
				If strChar1 = "c" Then
						'Examina el segundo caracter del mensaje e informa en el formulario si hay persona o no
						Select Case strChar2
								Case "0"
										lblMensajes.Text = "Cabina del ascensor vacia"
								Case "1"
										lblMensajes.Text = "Cabina del ascensor con persona"
						End Select
				End If
				'Si el primer caracter del mensaje comienza por 'l'
				If strChar1 = "l" Then
						'Visualiza el valor del sensor de proximidad en el formulario
						lblSensor.Text = Mid(Mensaje, 2)
				End If
		End Sub
		Private Sub Controles(ByVal Habilitar As Boolean)
				'Habilita o desabilita los controles del formulario
				If Habilitar Then
						lblPuerto.Text = cboPuertos.Text
						grpPlanta.Enabled = True
						grpPresencia.Enabled = True
						btnAlarma.Enabled = True
				Else
						lblPuerto.Text = ""
						grpPlanta.Enabled = False
						grpPresencia.Enabled = False
						btnAlarma.Enabled = False
				End If
		End Sub
End Class