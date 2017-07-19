/*!	\class QCommandSerialPort
*
*	\brief G�re les tampons d'envoi de commandes et de r�ponses.
*
*
*	Permet d'envoyer des QSerialCommand et d'analyser les r�ponses. Quand une r�ponse correspond � un QSerialCommand envoy�e,
*	ceux-ci sont retir�s de leur tampon respectif et le signal responseMatchesCommand() est �mit.
*	Si l'appareil connect� peut envoyer des messages de lui m�me, il faut appeler la fonction setDeviceMessages()
*	afin de les reconna�tre pour �mettre le signal messageReceived() quand un message est re�u.
*	La gestion des tampons d'envoie d�pend de chaque mode d'op�ration des QSerialCommand envoy�s.
*
*
*	D�tails concernant les modes d'op�ration:
*
*	-QSerialCommand avec mode d'op�ration OperationMode::BlockingMode::Blocking : quand la r�ponse attendue sera re�ue,
*		la commande et la r�ponse seront retir�es de leur tampon, et la prochaine commande dans le tampon mCommandsToSend sera envoy�e.
*	-QSerialCommand avec mode d'op�ration OperationMode::BlockingMode::NonBlockingWithResponse : une fois envoy�, le prochain QSerialCommand dans mCommandsToSend sera directement envoy�.
*		Quand la r�ponse correspondante du premier est re�ue, il sera retir� du tampon mCommandsSent.
*	-QSerialCommand avec mode d'op�ration OperationMode::BlockingMode::NonBlockingNoResponse : une fois envoy�, le prochain QSerialCommand dans mCommandsToSend sera directement envoy�.
*
*	-QSerialCommand avec mode d'op�ration OperationMode::FluxMode::Push : des r�ponses en continue sont attendues jusqu'� ce que la commande qui l'arr�te soit envoy�e.
*		*Cette commande devra �tre ajout� � l'aide de la m�thode addPushModeStopCommand() dans le QSerialCommand en mode Push. Il sera alors retir� du tampon mCommandsSent.
*	-QSerialCommand avec mode d'op�ration OperationMode::FluxMode::Pull : au maximum une r�ponse est attendue.
*/


#ifndef QCOMMANDSERIALPORT_H
#define QCOMMANDSERIALPORT_H



#include <QList>
#include <QPair>
#include "QAsyncSerialPort.h"
#include "SerialCommand.h"
#include "SerialOperationMode.h"

class QVariant;
class QStringList;


class QCommandSerialPort : public QAsyncSerialPort
{
	Q_OBJECT

public:
	typedef QList<QPair<SerialCommand, QList<QVariant>>> CommandsAndParams;
	QCommandSerialPort(int sendBufferSize = 150, int responsesBufferSize = 15000); //change name
	~QCommandSerialPort();

	CommandsAndParams mCommandsToSend;// private (return const ref)
	CommandsAndParams mCommandsSent;
	QByteArray mResponses;
	SerialOperationMode mCurrentOperationMode;

	bool developmentMode() { return mDevelopmentMode; }
	void setDevelopmentMode(bool devMode);
	void setDeviceMessages(QStringList messages, QString terminator);


private:
	QStringList mDeviceMessages;
	QString mTerminator;
	QTimer mCommandTimer;
	int mSendBufferSize;
	int mResponsesSize;
	bool mDevelopmentMode;
	bool mWaitingForBlockingResponse;

	void sendFromBuffer();
	void readData();
	void analyseAllResponses();
	//bool emitIfResponseMatchesCommand(QSerialCommand command);
	QByteArray responseMatchingCommand(SerialCommand command);

	QByteArray takeFirstResponse();
	void removeFirstResponse(QByteArray data);
	//bool retrySend(QString command);
	bool alreadySent(QPair<SerialCommand, QList<QVariant>> commandAndParams) const;

	QByteArray mBlockingResponse;


	public slots:
	void writeToBuffer(QPair<SerialCommand const &, QList<QVariant>> command);
	QByteArray sendBlockingCommand(SerialCommand command, QList<QVariant> params);
	void manageMessageSent();
	virtual void closeSerialPort() override;

	private slots:
	void handleResponse(QByteArray data);
	void handlePullCommandTimeout();
	void handleDevelopmentMode(bool devMode);
	void handleDisconnectRequest();

signals:
	void responseMatchesCommand(QByteArray response, SerialCommand command);
	void messageReceived(QString message);
	void developmentModeSwitched(bool devMode);
	void sendBufferTooLarge(); //
	void responsesBufferTooLarge();
	void disconnectRequest();
	void blockingResponseReceived();
	void readySendBlocking();
};


#endif // QCOMMANDSERIALPORT_H
