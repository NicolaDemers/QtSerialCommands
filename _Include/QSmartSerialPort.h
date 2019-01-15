#pragma once

/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

/*!	\class QSmartSerialPort
*
*	\brief G�re les tampons d'envoi de commandes et de r�ponses.
*
*
*	Permet d'envoyer des SerialCommand et d'analyser les r�ponses. Quand une r�ponse correspond � un SerialCommand envoy�e,
*	ceux-ci sont retir�s de leur tampon respectif et le signal matchingResponseReceived() est �mit.
*	Si l'appareil connect� peut envoyer des messages de lui m�me, il faut appeler la fonction setDeviceMessages()
*	afin de les reconna�tre pour �mettre le signal messageReceived() quand un message est re�u.
*	La gestion des tampons d'envoie d�pend de chaque mode d'op�ration des SerialCommand envoy�s.
*
*
*	D�tails concernant les modes d'op�ration:
*
*	-SerialCommand avec mode d'op�ration OperationMode::BlockingMode::Blocking : quand la r�ponse attendue sera re�ue,
*		la commande et la r�ponse seront retir�es de leur tampon, et la prochaine commande dans le tampon m_commandToSendList sera envoy�e.
*	-SerialCommand avec mode d'op�ration OperationMode::BlockingMode::NonBlockingWithResponse : une fois envoy�, le prochain SerialCommand dans m_commandToSendList sera directement envoy�.
*		Quand la r�ponse correspondante du premier est re�ue, il sera retir� du tampon m_sentCommandList.
*	-SerialCommand avec mode d'op�ration OperationMode::BlockingMode::NonBlockingNoResponse : une fois envoy�, le prochain SerialCommand dans m_commandToSendList sera directement envoy�.
*
*	-SerialCommand avec mode d'op�ration OperationMode::FluxMode::Push : des r�ponses en continue sont attendues jusqu'� ce que la commande qui l'arr�te soit envoy�e.
*		*Cette commande devra �tre ajout� � l'aide de la m�thode addPushModeStopCommand() dans le SerialCommand en mode Push. Il sera alors retir� du tampon m_sentCommandList.
*	-SerialCommand avec mode d'op�ration OperationMode::FluxMode::Pull : au maximum une r�ponse est attendue.
*/



#include <QList>
#include "QAsyncSerialPort.h"
#include "SerialCommand.h"
#include "SerialPortSettings.h"

#include "QSerialBuffer.h"
#include "QSerialResponseAnalyzer.h"
#include "QSerialCommandManager.h"
#include "SerialMessageFactory.h"

class QVariant;
class QStringList;


class QSmartSerialPort : public QAsyncSerialPort
{
	Q_OBJECT

public:
	QSmartSerialPort(const SerialMessageFactory & serialMessagesFactory, bool isAutoReconnecting = false);
	QSmartSerialPort();
	~QSmartSerialPort();

	void sendCommand(SerialCommand & command, QList<SerialCommandArg> args = QList<SerialCommandArg>());
	QByteArray sendBlockingCommandSync(SerialCommand & command, QList<SerialCommandArg> args = QList<SerialCommandArg>());
	void changeSerialPortSettings(SerialPortSettings * portSettings, bool blocking = true);
	void closePort();
	bool isBypassingSmartMatching() const { return m_isBypassingSmartMatchingMode; }
	void setBypassingSmartMatchingMode(bool isBypassing);

private:
	QSerialBuffer m_serialBuffer;
	const SerialMessages & m_serialMessages;
	bool m_gotDisconnected;
	bool m_hasChangedSettings;
	QTimer m_commandTimer;
	bool m_isBypassingSmartMatchingMode;
	SerialCommand * m_syncBlockingCommandSent;
	QByteArray m_syncBlockingResponse;
	bool m_isAutoReconnecting;

private slots:
	void handleCommandReadyToSend(const SerialCommand & command);
	void handleFoundMatchingResponse(const QByteArray & response, const SerialCommand & command);
	void handleResponse(QByteArray data);
	void handlePullCommandTimeout();
	void handleSmartMatchingModeChange(bool isBypassing);
	void handleSendCommandRequest(const SerialCommand & command);

signals:
	void sendCommandRequested(const SerialCommand & command);
	void matchingResponseReceived(const QByteArray & response, const SerialCommand & command);
	void messageReceived(const QByteArray & message, const QString & translation);
	void smartMatchingModeChanged(bool devMode);
	void changeSerialPortSettingsRequest(SerialPortSettings * portSettings);
	void commandTimedOut(QString command, QList<SerialCommandArg> args, int port);
	void changeSerialPortSettingsDone();
	void removeLastCommandSentRequest();
	void removeFirstCommandToSendRequest();
};