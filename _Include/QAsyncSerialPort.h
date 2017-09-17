/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

#pragma once


#include <QVector>
#include <QTimer>
#include <QSerialPort>




/*! \class QAsyncSerialPort
*
*	\brief Envoie et re�oit des donn�es au port s�rie.
*
*	G�re la connexion de l'appareil avec le port s�rie (openSerialPort() et closeSerialPort()).
*	Envoie des signaux par rapport aux erreurs de communication s�rie.
*/

class QAsyncSerialPort : public QSerialPort
{
	Q_OBJECT

public:
	QAsyncSerialPort();
	~QAsyncSerialPort();

	enum class BaudRate {
		BR600 = 600, BR1200 = 1200, BR2400 = 2400, BR4800 = 4800, BR9600 = 9600, BR14400 = 14400, BR19200 = 19200, BR28800 = 28800, BR38400 = 38400, BR56000 = 56000, BR57600 = 57600,
		BR115200 = 115200, BR128000 = 128000, BR230400 = 230400, BR256000 = 256000, BRUnknown = -1
	};

	int m_Timeout;

	bool sendMessage(QString message);
	bool sendMessage(QByteArray data);

private:
	QString mMessageToWrite;
	QTimer mTimer;
	qint64 mBytesWritten;

	public slots:
	bool openSerialPort(QString portName, BaudRate baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits, QSerialPort::FlowControl flowControl); // public??
	virtual void closeSerialPort();

	private slots:
	void readData();
	void handleTimeout();
	void handleBytesWritten(qint64 bytes);
	void handleError(QSerialPort::SerialPortError error);

signals:
	void dataRead(QByteArray data);
	//void responseRead(QString response);
	void connectionUpdated(bool connected, bool connectionFailed = false);
	void messageSent();
	void updated(QString message);

};


/*! \class QSerialSettings
*
*	\brief Conteneur des param�tres d'un appareil de communication s�rie. Permet la sauvegarde et le chargement de fichier ini.
*
*	save() pour sauvegarder et load() pour charger.
*
*/


class SerialSettings
{

public:
	SerialSettings(QAsyncSerialPort::BaudRate baudRate = QAsyncSerialPort::BaudRate::BR9600);
	SerialSettings(int comPort, QAsyncSerialPort::BaudRate baudRate = QAsyncSerialPort::BaudRate::BR9600);
	~SerialSettings();


	// Cles pour fichier INI
	static QString const PORTNAME;
	static QString const BAUDRATE;
	static QString const STOPBITS;
	static QString const DATABITS;
	static QString const PARITY;
	static QString const FLOWCONTROL;

	// Serial Port
	QString mPortName;
	QAsyncSerialPort::BaudRate mBaudRate;
	QSerialPort::StopBits mStopBits;
	QSerialPort::DataBits mDataBits;
	QSerialPort::Parity mParity;
	QSerialPort::FlowControl mFlowControl;


	void save(QString fileName);
	void load(QString fileName);
	void loadGeneric();

private:
	bool isValid();
};
