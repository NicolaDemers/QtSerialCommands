/* Copyright (C) Nicola Demers - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Nicola Demers <nicola.demers93@gmail.com>, July 2017
*/

/*!	\class QCommandSerialPort
*
*	\brief G�re les tampons d'envoi de commandes et de r�ponses.
*
*
*	Permet d'envoyer des QSerialCommand et d'analyser les r�ponses. Quand une r�ponse correspond � un QSerialCommand envoy�e,
*	ceux-ci sont retir�s de leur tampon respectif et le signal responseMatchingCommandReceived() est �mit.
*	Si l'appareil connect� peut envoyer des messages de lui m�me, il faut appeler la fonction setDeviceMessages()
*	afin de les reconna�tre pour �mettre le signal messageReceived() quand un message est re�u.
*	La gestion des tampons d'envoie d�pend de chaque mode d'op�ration des QSerialCommand envoy�s.
*
*
*	D�tails concernant les modes d'op�ration:
*
*	-QSerialCommand avec mode d'op�ration OperationMode::BlockingMode::Blocking : quand la r�ponse attendue sera re�ue,
*		la commande et la r�ponse seront retir�es de leur tampon, et la prochaine commande dans le tampon m_CommandsToSend sera envoy�e.
*	-QSerialCommand avec mode d'op�ration OperationMode::BlockingMode::NonBlockingWithResponse : une fois envoy�, le prochain QSerialCommand dans m_CommandsToSend sera directement envoy�.
*		Quand la r�ponse correspondante du premier est re�ue, il sera retir� du tampon m_CommandsSent.
*	-QSerialCommand avec mode d'op�ration OperationMode::BlockingMode::NonBlockingNoResponse : une fois envoy�, le prochain QSerialCommand dans m_CommandsToSend sera directement envoy�.
*
*	-QSerialCommand avec mode d'op�ration OperationMode::FluxMode::Push : des r�ponses en continue sont attendues jusqu'� ce que la commande qui l'arr�te soit envoy�e.
*		*Cette commande devra �tre ajout� � l'aide de la m�thode addPushModeStopCommand() dans le QSerialCommand en mode Push. Il sera alors retir� du tampon m_CommandsSent.
*	-QSerialCommand avec mode d'op�ration OperationMode::FluxMode::Pull : au maximum une r�ponse est attendue.
*/


#ifndef QCOMMANDSERIALPORT_H
#define QCOMMANDSERIALPORT_H



#include <QList>
#include <QPair>
#include "QAsyncSerialPort.h"
#include "SerialCommand.h"
#include "SerialSettings.h"

#include "serialcommandslib_global.h"

class QVariant;
class QStringList;


class SERIALCOMMANDSLIB_EXPORT QCommandSerialPort : public QAsyncSerialPort
{
	Q_OBJECT

public:
	QCommandSerialPort(int sendBufferSize = 150, int responsesBufferSize = 15000); //change name
	~QCommandSerialPort();

	QList<SerialCommand> m_CommandsToSend;// private (return const ref)
	QList<SerialCommand> m_CommandsSent;
	QByteArray m_Responses;
	SerialOperationMode m_CurrentOperationMode;

	bool developmentMode() { return m_DevelopmentMode; }
	void setDevelopmentMode(bool devMode);
	void setDeviceMessages(QStringList messages, QString terminator);

	void changeSerialSettings(SerialSettings * portSettings);

	void removeLastCommandSent();
	void clearBuffers();

private:
	QStringList m_DeviceMessages;
	QString m_Terminator;
	QTimer m_CommandTimer;
	int m_SendBufferSize;
	int m_ResponsesSize;
	bool m_DevelopmentMode;
	SerialCommand * m_BlockingCommandSent;

	SerialCommand m_LastCommandSent;
	bool m_LastCommandIsBlocking;
	bool m_ResponseMatchesLastCommand;

	bool m_GotDisconnected;
	bool m_HasChangedSettings;

	QByteArray m_BlockingResponse;

	void sendFromBuffer();
	void readData();
	void analyseAllResponses();
	//bool emitIfResponseMatchesCommand(QSerialCommand command);
	QByteArray responseMatchingCommand(SerialCommand command);

	QByteArray takeFirstResponse();
	void removeFirstResponse(QByteArray data);
	//bool retrySend(QString command);
	bool alreadySent(SerialCommand command) const;
	
	void clearBuffersNow();

public slots:
	void writeToBuffer(SerialCommand const & command);
	QByteArray sendBlockingCommand(SerialCommand command, QList<QVariant> params);
	void manageMessageSent();
	virtual void closePort() override;

private slots:
	void handleResponse(QByteArray data);
	void handlePullCommandTimeout();
	void handleDevelopmentMode(bool devMode);
	void handleDisconnectRequest();
	void handleChangeSerialSettingsRequest(SerialSettings * portSettings);
	void handleClearBuffersRequest();
	void handleRemoveLastCommandSent();
	void handleRemoveFirstCommandToSend();
	void handleSendCommandRequest(SerialCommand command);

signals:
	void responseMatchingCommandReceived(QByteArray const &response, SerialCommand const &command);
	void messageReceived(QString const &message);
	void developmentModeSwitched(bool devMode);
	void sendBufferTooLarge(); //
	void responsesBufferTooLarge();
	void disconnectRequest();
	void disconnectDone();
	void blockingResponseReceived();
	void changeSerialSettingsRequest(SerialSettings * portSettings);
	void changeSerialSettingsDone();
	void commandTimedOut(QString command, QList<QVariant> args, int port);
	void clearBuffersRequest();
	void removeLastCommandSentRequest();
	void removeFirstCommandToSendRequest();
	void sendCommandRequest(SerialCommand command);
};


#endif // QCOMMANDSERIALPORT_H
