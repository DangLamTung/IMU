from PyQt5.QtWidgets import QApplication,QTabWidget, QWidget, QPushButton, QHBoxLayout,QVBoxLayout,QSlider,QLabel,QMessageBox,QListWidget,QTextEdit

def get_layout(main_layout):
	
	slider = QSlider()
	slider.setValue(1000)
	slider.setMinimum(1000)
	slider.setMaximum(2000)
	slider.valueChanged.connect(update_slider)

	slider1 = QSlider()
	slider1.setValue(1000)
	slider1.setMinimum(1000)
	slider1.setMaximum(2000)
	slider1.valueChanged.connect(update_slider)

	slider2 = QSlider()
	slider2.setValue(1000)
	slider2.setMinimum(1000)
	slider2.setMaximum(2000)
	slider2.valueChanged.connect(update_slider)

	slider3 = QSlider()
	slider3.setValue(1000)
	slider3.setMinimum(1000)
	slider3.setMaximum(2000)
	slider3.valueChanged.connect(update_slider)

	slider4 = QSlider()
	slider4.setValue(1000)
	slider4.setMinimum(1000)
	slider4.setMaximum(2000)
	slider4.valueChanged.connect(setPID_all)

	slider5 = QSlider()
	slider5.setValue(0)
	slider5.setMaximum(2000)
	slider5.valueChanged.connect(update_slider)

	slider6 = QSlider()
	slider6.setValue(0)
	slider6.setMaximum(2000)
	slider6.valueChanged.connect(update_slider)

	slider7 = QSlider()
	slider7.setValue(0)
	slider7.setMaximum(999)
	slider7.valueChanged.connect(update_slider)
	# Will print '5'

	layout = QHBoxLayout()
	layout_inner = QHBoxLayout()
	layout_inner1 = QHBoxLayout()
	layout_inner2 = QVBoxLayout()

	layout_value = QHBoxLayout()

	label = QLabel("Motor 1")
	label1 = QLabel("Motor 2")
	label2 = QLabel("Motor 3")

	label3 = QLabel("Motor 4")
	label4 = QLabel("All motor")
	label5 = QLabel("Kd 2")

	label6 = QLabel("Motor 1")
	label7 = QLabel("Motor 2")

	label_duty1 = QLabel("Gyro x")
	label_duty2 = QLabel("Gyro y")
	label_duty3 = QLabel("Gyro z")

	label_duty4 = QLabel("Acc x")
	label_duty5 = QLabel("Acc y")
	label_duty6 = QLabel("Acc z")

	label_duty7 = QLabel("Roll")
	label_duty8 = QLabel("Pitch")
	label_duty9 = QLabel("Yaw")

	label_duty10 = QLabel("Time: ")

	connect_button = QPushButton('Connect COM')
	connect_button.clicked.connect(connectCOM)

	detatch_button = QPushButton('Disconnect COM')
	detatch_button.clicked.connect(detachCOM)

	layout_inner2.addWidget(connect_button)
	layout_inner2.addWidget(detatch_button)

	list_widget = QListWidget()

	list_widget.insertItem(0, "/dev/ttyUSB0" )
	list_widget.insertItem(1, "/dev/ttyUSB1" )
	list_widget.insertItem(2, "/dev/ttyUSB2" )
	list_widget.insertItem(3, "/dev/ttyUSB3" )
	list_widget.insertItem(4, "/dev/ttyUSB4" )
	list_widget.insertItem(5, "/dev/ttyUSB5" )
	list_widget.insertItem(6, "/dev/ttyUSB6" )
	list_widget.insertItem(7, "/dev/ttyUSB7" )

	list_widget.clicked.connect(list_clicked)
	layout_inner.addWidget(list_widget)
	layout_inner.addLayout(layout_inner2)

	layout.addWidget(slider)
	layout.addWidget(label)

	layout.addWidget(slider1)
	layout.addWidget(label1)

	layout.addWidget(slider2)
	layout.addWidget(label2)

	layout.addWidget(slider3)
	layout.addWidget(label3)

	layout.addWidget(slider4)
	layout.addWidget(label4)

	layout.addWidget(slider5)
	layout.addWidget(label5)

	layout.addWidget(slider6)
	layout.addWidget(label6)

	layout.addWidget(slider7)
	layout.addWidget(label7)

	layout.addStretch(2)

	layout.addLayout(layout_inner)


	main_layout.addLayout(layout)

	button = QPushButton('Set PID')
	button.clicked.connect(setPID)

	button1 = QPushButton('Start')
	button1.clicked.connect(startRun)

	button2 = QPushButton('Stop')
	button2.clicked.connect(stopRun)

	layout_inner1.addWidget(button)
	layout_inner1.addWidget(button1)
	layout_inner1.addWidget(button2)

	textEdit = QTextEdit()

	layout_value.addWidget(label_duty1)
	layout_value.addWidget(label_duty2)
	layout_value.addWidget(label_duty3)
	layout_value.addWidget(label_duty10)

	main_layout.addLayout(layout_inner1)
	main_layout.addLayout(layout_value)

	plot_batch = QVBoxLayout()
	layout_plot = QHBoxLayout()
	layout_plot.addWidget(plot_uart)
	layout_plot.addWidget(plot_uart1)
	layout_plot.addWidget(plot_uart2)

	layout_plot1 = QHBoxLayout()
	layout_plot1.addWidget(plot_uart3)
	layout_plot1.addWidget(plot_uart4)
	layout_plot1.addWidget(plot_uart5)

	layout_plot2 = QHBoxLayout()
	layout_plot2.addWidget(plot_uart6)
	layout_plot2.addWidget(plot_uart7)
	layout_plot2.addWidget(plot_uart8)

	plot_batch.addLayout(layout_plot)
	plot_batch.addLayout(layout_plot1)
	plot_batch.addLayout(layout_plot2)

	main_layout.addLayout(plot_batch)

	main_layout.addWidget(textEdit)
