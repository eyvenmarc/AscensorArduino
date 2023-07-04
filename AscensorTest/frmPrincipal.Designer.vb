<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmPrincipal
		Inherits System.Windows.Forms.Form

		'Form reemplaza a Dispose para limpiar la lista de componentes.
		<System.Diagnostics.DebuggerNonUserCode()> _
		Protected Overrides Sub Dispose(ByVal disposing As Boolean)
				Try
						If disposing AndAlso components IsNot Nothing Then
								components.Dispose()
						End If
				Finally
						MyBase.Dispose(disposing)
				End Try
		End Sub

		'Requerido por el Diseñador de Windows Forms
		Private components As System.ComponentModel.IContainer

		'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
		'Se puede modificar usando el Diseñador de Windows Forms.  
		'No lo modifique con el editor de código.
		<System.Diagnostics.DebuggerStepThrough()> _
		Private Sub InitializeComponent()
				Me.components = New System.ComponentModel.Container()
				Me.comArduino = New System.IO.Ports.SerialPort(Me.components)
				Me.grpPlanta = New System.Windows.Forms.GroupBox()
		Me.chkPersona = New System.Windows.Forms.CheckBox()
		Me.btnPlanta3 = New System.Windows.Forms.Button()
		Me.btnPlanta2 = New System.Windows.Forms.Button()
		Me.btnPlanta1 = New System.Windows.Forms.Button()
		Me.btnPlanta0 = New System.Windows.Forms.Button()
		Me.GroupBox2 = New System.Windows.Forms.GroupBox()
		Me.grpPresencia = New System.Windows.Forms.GroupBox()
		Me.lblSensor = New System.Windows.Forms.Label()
		Me.btnConsultarSensor = New System.Windows.Forms.Button()
		Me.btnCambiarLimite = New System.Windows.Forms.Button()
		Me.txtLimite = New System.Windows.Forms.TextBox()
		Me.GroupBox1 = New System.Windows.Forms.GroupBox()
		Me.btnAceptarCOM = New System.Windows.Forms.Button()
		Me.cboPuertos = New System.Windows.Forms.ComboBox()
		Me.btnAlarma = New System.Windows.Forms.Button()
		Me.GroupBox3 = New System.Windows.Forms.GroupBox()
		Me.lblMensajes = New System.Windows.Forms.Label()
		Me.lblPlanta = New System.Windows.Forms.Label()
		Me.Label1 = New System.Windows.Forms.Label()
		Me.lblPuerto = New System.Windows.Forms.Label()
		Me.grpPlanta.SuspendLayout()
		Me.GroupBox2.SuspendLayout()
		Me.grpPresencia.SuspendLayout()
		Me.GroupBox1.SuspendLayout()
		Me.GroupBox3.SuspendLayout()
		Me.SuspendLayout()
		'
		'comArduino
		'
		Me.comArduino.PortName = "COM10"
		'
		'grpPlanta
		'
		Me.grpPlanta.Controls.Add(Me.chkPersona)
		Me.grpPlanta.Controls.Add(Me.btnPlanta3)
		Me.grpPlanta.Controls.Add(Me.btnPlanta2)
		Me.grpPlanta.Controls.Add(Me.btnPlanta1)
		Me.grpPlanta.Controls.Add(Me.btnPlanta0)
		Me.grpPlanta.Enabled = False
		Me.grpPlanta.Location = New System.Drawing.Point(386, 84)
		Me.grpPlanta.Name = "grpPlanta"
		Me.grpPlanta.Size = New System.Drawing.Size(174, 390)
		Me.grpPlanta.TabIndex = 0
		Me.grpPlanta.TabStop = False
		Me.grpPlanta.Text = "Planta"
		'
		'chkPersona
		'
		Me.chkPersona.AutoSize = True
		Me.chkPersona.Location = New System.Drawing.Point(33, 348)
		Me.chkPersona.Name = "chkPersona"
		Me.chkPersona.Size = New System.Drawing.Size(115, 17)
		Me.chkPersona.TabIndex = 4
		Me.chkPersona.Tag = "0"
		Me.chkPersona.Text = "Persona en cabina"
		Me.chkPersona.UseVisualStyleBackColor = True
		'
		'btnPlanta3
		'
		Me.btnPlanta3.Location = New System.Drawing.Point(47, 28)
		Me.btnPlanta3.Name = "btnPlanta3"
		Me.btnPlanta3.Size = New System.Drawing.Size(87, 49)
		Me.btnPlanta3.TabIndex = 3
		Me.btnPlanta3.Text = "Planta 3"
		Me.btnPlanta3.UseVisualStyleBackColor = True
		'
		'btnPlanta2
		'
		Me.btnPlanta2.Location = New System.Drawing.Point(47, 112)
		Me.btnPlanta2.Name = "btnPlanta2"
		Me.btnPlanta2.Size = New System.Drawing.Size(87, 49)
		Me.btnPlanta2.TabIndex = 2
		Me.btnPlanta2.Text = "Planta 2"
		Me.btnPlanta2.UseVisualStyleBackColor = True
		'
		'btnPlanta1
		'
		Me.btnPlanta1.Location = New System.Drawing.Point(47, 192)
		Me.btnPlanta1.Name = "btnPlanta1"
		Me.btnPlanta1.Size = New System.Drawing.Size(87, 49)
		Me.btnPlanta1.TabIndex = 1
		Me.btnPlanta1.Text = "Planta 1"
		Me.btnPlanta1.UseVisualStyleBackColor = True
		'
		'btnPlanta0
		'
		Me.btnPlanta0.Location = New System.Drawing.Point(47, 274)
		Me.btnPlanta0.Name = "btnPlanta0"
		Me.btnPlanta0.Size = New System.Drawing.Size(87, 49)
		Me.btnPlanta0.TabIndex = 0
		Me.btnPlanta0.Text = "Planta 0"
		Me.btnPlanta0.UseVisualStyleBackColor = True
		'
		'GroupBox2
		'
		Me.GroupBox2.Controls.Add(Me.grpPresencia)
		Me.GroupBox2.Controls.Add(Me.GroupBox1)
		Me.GroupBox2.Location = New System.Drawing.Point(55, 84)
		Me.GroupBox2.Name = "GroupBox2"
		Me.GroupBox2.Size = New System.Drawing.Size(189, 390)
		Me.GroupBox2.TabIndex = 1
		Me.GroupBox2.TabStop = False
		Me.GroupBox2.Text = "Configuración"
		'
		'grpPresencia
		'
		Me.grpPresencia.Controls.Add(Me.lblSensor)
		Me.grpPresencia.Controls.Add(Me.btnConsultarSensor)
		Me.grpPresencia.Controls.Add(Me.btnCambiarLimite)
		Me.grpPresencia.Controls.Add(Me.txtLimite)
		Me.grpPresencia.Enabled = False
		Me.grpPresencia.Location = New System.Drawing.Point(24, 190)
		Me.grpPresencia.Name = "grpPresencia"
		Me.grpPresencia.Size = New System.Drawing.Size(142, 185)
		Me.grpPresencia.TabIndex = 4
		Me.grpPresencia.TabStop = False
		Me.grpPresencia.Text = "Sensor de presencia"
		'
		'lblSensor
		'
		Me.lblSensor.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom), System.Windows.Forms.AnchorStyles)
		Me.lblSensor.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.lblSensor.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.lblSensor.Location = New System.Drawing.Point(30, 24)
		Me.lblSensor.Name = "lblSensor"
		Me.lblSensor.Size = New System.Drawing.Size(93, 19)
		Me.lblSensor.TabIndex = 8
		Me.lblSensor.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		'
		'btnConsultarSensor
		'
		Me.btnConsultarSensor.Location = New System.Drawing.Point(28, 56)
		Me.btnConsultarSensor.Name = "btnConsultarSensor"
		Me.btnConsultarSensor.Size = New System.Drawing.Size(97, 29)
		Me.btnConsultarSensor.TabIndex = 7
		Me.btnConsultarSensor.Text = "Consultar"
		Me.btnConsultarSensor.UseVisualStyleBackColor = True
		'
		'btnCambiarLimite
		'
		Me.btnCambiarLimite.Location = New System.Drawing.Point(28, 138)
		Me.btnCambiarLimite.Name = "btnCambiarLimite"
		Me.btnCambiarLimite.Size = New System.Drawing.Size(97, 28)
		Me.btnCambiarLimite.TabIndex = 5
		Me.btnCambiarLimite.Text = "Cambiar"
		Me.btnCambiarLimite.UseVisualStyleBackColor = True
		'
		'txtLimite
		'
		Me.txtLimite.Location = New System.Drawing.Point(28, 112)
		Me.txtLimite.Name = "txtLimite"
		Me.txtLimite.Size = New System.Drawing.Size(97, 20)
		Me.txtLimite.TabIndex = 4
		Me.txtLimite.TextAlign = System.Windows.Forms.HorizontalAlignment.Center
		'
		'GroupBox1
		'
		Me.GroupBox1.Controls.Add(Me.lblPuerto)
		Me.GroupBox1.Controls.Add(Me.btnAceptarCOM)
		Me.GroupBox1.Controls.Add(Me.cboPuertos)
		Me.GroupBox1.Location = New System.Drawing.Point(24, 19)
		Me.GroupBox1.Name = "GroupBox1"
		Me.GroupBox1.Size = New System.Drawing.Size(142, 165)
		Me.GroupBox1.TabIndex = 3
		Me.GroupBox1.TabStop = False
		Me.GroupBox1.Text = "Puerto COM"
		'
		'btnAceptarCOM
		'
		Me.btnAceptarCOM.Location = New System.Drawing.Point(27, 103)
		Me.btnAceptarCOM.Name = "btnAceptarCOM"
		Me.btnAceptarCOM.Size = New System.Drawing.Size(97, 39)
		Me.btnAceptarCOM.TabIndex = 5
		Me.btnAceptarCOM.Text = "Aceptar"
		Me.btnAceptarCOM.UseVisualStyleBackColor = True
		'
		'cboPuertos
		'
		Me.cboPuertos.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom), System.Windows.Forms.AnchorStyles)
		Me.cboPuertos.FormattingEnabled = True
		Me.cboPuertos.Location = New System.Drawing.Point(27, 24)
		Me.cboPuertos.Name = "cboPuertos"
		Me.cboPuertos.Size = New System.Drawing.Size(98, 21)
		Me.cboPuertos.TabIndex = 3
		'
		'btnAlarma
		'
		Me.btnAlarma.Enabled = False
		Me.btnAlarma.FlatStyle = System.Windows.Forms.FlatStyle.Flat
		Me.btnAlarma.Location = New System.Drawing.Point(271, 311)
		Me.btnAlarma.Name = "btnAlarma"
		Me.btnAlarma.Size = New System.Drawing.Size(79, 67)
		Me.btnAlarma.TabIndex = 2
		Me.btnAlarma.Text = "Activar Alarma"
		Me.btnAlarma.UseVisualStyleBackColor = True
		'
		'GroupBox3
		'
		Me.GroupBox3.Controls.Add(Me.lblMensajes)
		Me.GroupBox3.Location = New System.Drawing.Point(31, 12)
		Me.GroupBox3.Name = "GroupBox3"
		Me.GroupBox3.Size = New System.Drawing.Size(553, 58)
		Me.GroupBox3.TabIndex = 3
		Me.GroupBox3.TabStop = False
		'
		'lblMensajes
		'
		Me.lblMensajes.Font = New System.Drawing.Font("Microsoft Sans Serif", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.lblMensajes.ForeColor = System.Drawing.Color.Blue
		Me.lblMensajes.Location = New System.Drawing.Point(21, 16)
		Me.lblMensajes.Name = "lblMensajes"
		Me.lblMensajes.Size = New System.Drawing.Size(516, 28)
		Me.lblMensajes.TabIndex = 0
		Me.lblMensajes.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		'
		'lblPlanta
		'
		Me.lblPlanta.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.lblPlanta.Font = New System.Drawing.Font("Microsoft Sans Serif", 72.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.lblPlanta.Location = New System.Drawing.Point(269, 147)
		Me.lblPlanta.Name = "lblPlanta"
		Me.lblPlanta.Size = New System.Drawing.Size(92, 98)
		Me.lblPlanta.TabIndex = 4
		'
		'Label1
		'
		Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.Label1.Location = New System.Drawing.Point(269, 112)
		Me.Label1.Name = "Label1"
		Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.Label1.Size = New System.Drawing.Size(92, 27)
		Me.Label1.TabIndex = 5
		Me.Label1.Text = "Nº Planta"
		Me.Label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		'
		'lblPuerto
		'
		Me.lblPuerto.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
		Me.lblPuerto.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
		Me.lblPuerto.Location = New System.Drawing.Point(26, 62)
		Me.lblPuerto.Name = "lblPuerto"
		Me.lblPuerto.RightToLeft = System.Windows.Forms.RightToLeft.No
		Me.lblPuerto.Size = New System.Drawing.Size(98, 22)
		Me.lblPuerto.TabIndex = 6
		Me.lblPuerto.TextAlign = System.Drawing.ContentAlignment.MiddleCenter
		'
		'frmPrincipal
		'
		Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
		Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
		Me.ClientSize = New System.Drawing.Size(627, 486)
		Me.Controls.Add(Me.Label1)
		Me.Controls.Add(Me.lblPlanta)
		Me.Controls.Add(Me.GroupBox3)
		Me.Controls.Add(Me.btnAlarma)
		Me.Controls.Add(Me.GroupBox2)
		Me.Controls.Add(Me.grpPlanta)
		Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
		Me.Name = "frmPrincipal"
		Me.Text = "Test Ascensor Arduino"
		Me.grpPlanta.ResumeLayout(False)
		Me.grpPlanta.PerformLayout()
		Me.GroupBox2.ResumeLayout(False)
		Me.grpPresencia.ResumeLayout(False)
		Me.grpPresencia.PerformLayout()
		Me.GroupBox1.ResumeLayout(False)
		Me.GroupBox3.ResumeLayout(False)
		Me.ResumeLayout(False)

	End Sub

	Friend WithEvents comArduino As IO.Ports.SerialPort
		Friend WithEvents grpPlanta As GroupBox
		Friend WithEvents btnPlanta0 As Button
	Friend WithEvents btnPlanta1 As Button
	Friend WithEvents btnPlanta3 As Button
	Friend WithEvents btnPlanta2 As Button
	Friend WithEvents chkPersona As CheckBox
	Friend WithEvents GroupBox2 As GroupBox
	Friend WithEvents GroupBox1 As GroupBox
	Friend WithEvents btnAceptarCOM As Button
	Friend WithEvents cboPuertos As ComboBox
	Friend WithEvents grpPresencia As GroupBox
	Friend WithEvents btnConsultarSensor As Button
	Friend WithEvents btnCambiarLimite As Button
	Friend WithEvents txtLimite As TextBox
	Friend WithEvents btnAlarma As Button
	Friend WithEvents GroupBox3 As GroupBox
	Friend WithEvents lblMensajes As Label
	Friend WithEvents lblSensor As Label
	Friend WithEvents lblPlanta As Label
	Friend WithEvents Label1 As Label
	Friend WithEvents lblPuerto As Label
End Class
