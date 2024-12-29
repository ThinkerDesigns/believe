#ifndef WEATHERDATAFETCHER_H
#define WEATHERDATAFETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WeatherDataFetcher : public QObject {
    Q_OBJECT

public:
    explicit WeatherDataFetcher(QObject *parent = nullptr);
    void fetchWeatherData(const QString &location);

private slots:
    void onDataReceived(QNetworkReply *reply);

private:
    QNetworkAccessManager *networkManager;
    const QString apiKey = "your_openweathermap_api_key";  // Replace with your API key
    const QString apiUrl = "http://api.openweathermap.org/data/2.5/weather";
};

#endif // WEATHERDATAFETCHER_H
