#include "ui.h"

UI::UI(int argc, char *argv[], std::shared_ptr<Buffer> buffer) {
	this->app = new QApplication(argc, argv);
	this->window = new QWidget;
	this->frontFrame = new QLabel(window);
	this->leftFrame = new QLabel(window);
	this->rightFrame = new QLabel(window);
	this->backFrame = new QLabel(window);
	this->imuAcc = new QLabel(window);
	this->imuGyro = new QLabel(window);
	this->imuMag = new QLabel(window);
	this->steering = new QLabel(window);
	this->speed = new QLabel(window);
	this->throttle = new QLabel(window);
	this->brake = new QLabel(window);
	this->timer = new QTimer(window);
	this->buffer = buffer;
	this->leftFrontFrames = new QHBoxLayout;
	this->rightBackFrames = new QHBoxLayout;
	this->framesLayout = new QVBoxLayout;
	this->textDataLayout = new QVBoxLayout;
	this->dataLayout = new QVBoxLayout;
	this->mainLayout = new QHBoxLayout;
	run();
}

void UI::run() {

    window->setWindowTitle("Real-Time Automotive Data Visualization");
    window->showMaximized();

    //view->resize(200, 200);
    QWebEngineView *view = new QWebEngineView();
    view->setUrl(QUrl::fromLocalFile("/home/lama/Desktop/Training/proj/map.html"));
    view->resize(100, 50);
    view->show();

    // Set a background color
    QPalette pal = window->palette();
    pal.setColor(QPalette::Window, QColor(45, 45, 48));  // Dark grey background
    window->setAutoFillBackground(true);
    window->setPalette(pal);
    

    leftFrontFrames->addWidget(leftFrame);
    leftFrontFrames->addWidget(frontFrame);
    
    rightBackFrames->addWidget(rightFrame);
    rightBackFrames->addWidget(backFrame);
    
    framesLayout->addLayout(leftFrontFrames);
    framesLayout->addLayout(rightBackFrames);
    
    textDataLayout->addWidget(imuAcc);
    textDataLayout->addWidget(imuGyro);
    textDataLayout->addWidget(imuMag);
    textDataLayout->addWidget(steering);
    textDataLayout->addWidget(speed);
    textDataLayout->addWidget(throttle);
    textDataLayout->addWidget(brake);
    
    dataLayout->addLayout(textDataLayout);
    dataLayout->addSpacing(2);
    //dataLayout->addStretch();
    dataLayout->addWidget(view);
    
    mainLayout->addLayout(dataLayout);
    mainLayout->addLayout(framesLayout);
    
    QObject::connect(view->page(), &QWebEnginePage::loadFinished, [this, view](bool success) {
    	if (success) {
        	qDebug() << "Page loaded successfully!";
        	// Now it's safe to run JavaScript
        	QObject::connect(timer, &QTimer::timeout, [this, view]() {
        	    updateImage(leftFrame, SensorType::LeftCamera);
        	    updateImage(frontFrame, SensorType::FrontCamera);
        	    updateImage(rightFrame, SensorType::RightCamera);
        	    updateImage(backFrame, SensorType::BackCamera);
        	    
        	    auto gpsObject = buffer->getDataSource<GPSData>(SensorType::GPS);
        	    auto pair = std::any_cast<std::pair<double,double>>(gpsObject->getData());
        	    double lat = pair.first;
            	    double longi = pair.second;
        	    
        	    
            	    if (lat != 0 && longi != 0){
            	    	QString jsCode = QString("updateLocation(%1, %2);").
            	    			arg(lat).arg(longi);
            	    	view->page()->runJavaScript(jsCode, [](const QVariant &result) {});
		    }
		    updateIMUData();
		    updateTextData<StearingData>(steering, SensorType::Steering, "Steering");
		    updateTextData<SpeedData>(speed, SensorType::Speed, "Speed");
		    updateTextData<ThrottleData>(throttle, SensorType::Throttle, "Throttle");
		    updateTextData<BrakeData>(brake, SensorType::Brake, "Brake");
        	});
        	timer->start(read_buffer_rate);
    	} else {
        	qDebug() << "Failed to load the page.";
    	}
    });

    
    view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

    window->setLayout(mainLayout);
    window->show();
    app->exec();
    delete(view);
    
}

QImage UI::matToQImage(cv::Mat mat) {
    	cv::Mat rgb;
    	cv::cvtColor(mat, rgb, cv::COLOR_BGR2RGB);
    	QImage qimage1(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
	QImage image = qimage1.copy();
	return image;
}

void UI::updateImage(QLabel* label, SensorType key) {
        auto camera = buffer->getDataSource<CameraData>(key);
        cv::Mat image = std::any_cast<cv::Mat>(camera->getData());
    	if (!image.empty()) {
    		cv::Mat resizedImage;
    		cv::resize(image, resizedImage, cv::Size(image_width, image_height));
        	
        	QImage qimage = matToQImage(resizedImage);
        	label->setPixmap(QPixmap::fromImage(qimage));
        }
}

void UI::updateIMUData() {
    auto imu = buffer->getDataSource<IMUData>(SensorType::IMU);
    auto data = std::any_cast<std::array<std::array<double, 3>, 3>>(imu->getData());
    
    QString acc = QString("Accelerations: %1, %2, %3")
                    .arg(data[0][0])
                    .arg(data[0][1])
                    .arg(data[0][2]);
    
    QString gyro = QString("Gyroscopic: %1, %2, %3")
                    .arg(data[1][0])
                    .arg(data[1][1])
                    .arg(data[1][2]);
    
    QString mag = QString("Magnetic: %1, %2, %3")
                    .arg(data[2][0])
                    .arg(data[2][1])
                    .arg(data[2][2]);

    // Convert the text to pixmap
    imuAcc->setPixmap(createPixmapFromText(acc));
    imuGyro->setPixmap(createPixmapFromText(gyro));
    imuMag->setPixmap(createPixmapFromText(mag));
}

template<typename T>
void UI::updateTextData(QLabel* label, SensorType key, std::string title) {
	auto object = buffer->getDataSource<T>(key);
	auto value = std::any_cast<double>(object->getData());
	
	title += ": " + std::to_string(value);
	
	QString data = QString::fromStdString(title);
	
	label->setPixmap(createPixmapFromText(data));
}

QPixmap UI::createPixmapFromText(const QString& text) {
    QFont font("Arial", 15);
    QFontMetrics metrics(font);
    int width = metrics.horizontalAdvance(text);
    int height = metrics.height();

    QPixmap pixmap(width, height);
    pixmap.fill(Qt::transparent);  // Fill with transparent background

    QPainter painter(&pixmap);
    painter.setFont(font);
    painter.setPen(Qt::white);  // Set text color (you can customize this)
    painter.drawText(0, metrics.ascent(), text);
    painter.end();

    return pixmap;
}


UI::~UI() {
    	delete(this->app);
	delete(this->window);
	delete(this->frontFrame);
	delete(this->leftFrame);
	delete(this->rightFrame);
	delete(this->backFrame);
	delete(this->imuAcc);
	delete(this->imuGyro);
	delete(this->imuMag);
	delete(this->steering);
	delete(this->speed);
	delete(this->throttle);
	delete(this->brake);
	delete(this->timer);
	delete(this->leftFrontFrames);
	delete(this->rightBackFrames);
	delete(this->framesLayout);
	delete(this->textDataLayout);
	delete(this->dataLayout);
	delete(this->mainLayout);
}


