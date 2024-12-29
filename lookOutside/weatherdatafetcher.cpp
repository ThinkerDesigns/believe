#include "weatherdatafetcher.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

WeatherDataFetcher::WeatherDataFetcher(QObject *parent)
    : QObject(parent),
    networkManager(new QNetworkAccessManager(this)) {

    connect(networkManager, &QNetworkAccessManager::finished, this, &WeatherDataFetcher::onDataReceived);
}

void WeatherDataFetcher::fetchWeatherData(const QString &location) {
    QUrl url(apiUrl);
    QUrlQuery query;
    query.addQueryItem("q", location);
    query.addQueryItem("appid", apiKey);
    query.addQueryItem("units", "metric");
    url.setQuery(query);

    networkManager->get(QNetworkRequest(url));
}

void WeatherDataFetcher::onDataReceived(QNetworkReply *reply) {
    if (reply->error()) {
        // Handle error
    } else {
        QByteArray responseData = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = doc.object();
        // Parse and display the data here
    }
    reply->deleteLater();
}
