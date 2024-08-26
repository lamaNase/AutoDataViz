#pragma once

#include <iostream>
#include <string>
#include <QApplication>
#include <QMainWindow>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QImage>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <QPainter>
#include <QFontMetrics>
#include "../buffer/buffer.h"
#include "../DataSources/headers/headers.h"
#include "../constants.h"

class UI {
private:
	QApplication* app;
	QWidget* window;
	QLabel* frontFrame;
	QLabel* leftFrame;
	QLabel* rightFrame;
	QLabel* backFrame;
	QLabel* imuAcc;
	QLabel* imuGyro;
	QLabel* imuMag;
	QLabel* steering;
	QLabel* speed;
	QLabel* throttle;
	QLabel* brake;
	QTimer* timer;
	std::shared_ptr<Buffer> buffer;
	
	// Layouts
	QHBoxLayout *leftFrontFrames;
	QHBoxLayout *rightBackFrames;
	QVBoxLayout *framesLayout;
	QVBoxLayout *textDataLayout;
	QVBoxLayout *dataLayout;
	QHBoxLayout *mainLayout;

public:
	UI(int argc, char *argv[], std::shared_ptr<Buffer> buffer);
	~UI();
	void run();
	QImage matToQImage(cv::Mat mat);
	void updateImage(QLabel* label, SensorType key);
	void updateIMUData();
	template<typename T>
	void updateTextData(QLabel* label, SensorType key, std::string title);
	QPixmap createPixmapFromText(const QString& text);
};
