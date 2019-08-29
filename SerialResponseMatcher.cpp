#include "SerialResponseMatcher.h"


SerialResponseMatcher::SerialResponseMatcher()
{
}

SerialResponseMatcher::SerialResponseMatcher(const SerialMessages & serialMessages) :
	m_serialMessages{ serialMessages }
{
}

SerialResponseMatcher::~SerialResponseMatcher()
{
}

QByteArray SerialResponseMatcher::getCommandFirstMatch(const QByteArray & responseBuffer, const SerialCommand & command) const
{
	switch (command.getMatchType())
	{
		case MatchType::Regex:
			return getRegexMatch(responseBuffer, command);
		case MatchType::ExpectedResponses:
			return getExpectedResponsesMatch(responseBuffer, command);
		case MatchType::NbExpectedBytes:
			return getNbExpectedBytesMatch(responseBuffer, command);
		default:
			return QByteArray();
	}			
}

QByteArrayList SerialResponseMatcher::getMessages(const QByteArray& responsesBuffer) const
{
	QMap<int, QByteArray> responseMap;
	QByteArrayList sortedResponseList;
	int index = std::numeric_limits<int>::max();

	for (QByteArray expectedResponse : m_serialMessages.getMessageList())
	{
		index = responsesBuffer.indexOf(expectedResponse);
		if (index != -1)
		{
			responseMap[index] = expectedResponse;
		}
	}

	if (responseMap.size() <= 1) 
	{
		return responseMap.values();
	}

	QList<int> sortedKeys = responseMap.keys();
	qSort(sortedKeys);
	for (int key : responseMap.keys()) {
		sortedResponseList.append(responseMap[key]);
	}

	return sortedResponseList;
}

QByteArray SerialResponseMatcher::getRegexMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const
{
	QRegularExpressionMatch match = command.getResponseRegex().match(responsesBuffer);
	if (match.hasMatch())
	{
		QString firstMatch = match.captured(0);
		return firstMatch.toLatin1();
	}
	return QByteArray();
}

QByteArray SerialResponseMatcher::getExpectedResponsesMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const
{
	QByteArray response;
	int index = std::numeric_limits<int>::max();
	for (QByteArray expectedResponse : command.getExpectedResponses())
	{
		if (responsesBuffer.indexOf(expectedResponse) != -1 && responsesBuffer.indexOf(expectedResponse) < index)
		{
			response = expectedResponse;
			index = responsesBuffer.indexOf(expectedResponse);
		}
	}
	return response;
}

QByteArray SerialResponseMatcher::getNbExpectedBytesMatch(const QByteArray & responsesBuffer, const SerialCommand & command) const
{
	QByteArray response;
	if (command.getNbBytesExpected() > 0 && responsesBuffer.size() >= command.getNbBytesExpected()) {
		response = responsesBuffer.left(command.getNbBytesExpected());
	}
	return response;
}
