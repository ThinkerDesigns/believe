#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

class WeatherWidget : public QWidget {
    Q_OBJECT
public:
    explicit WeatherWidget(QWidget *parent = nullptr);
    ~WeatherWidget();
private slots:
    void onWeatherButtonClicked();
    void onWeatherDataReceived(QNetworkReply *reply);
    void onUnitButtonClicked();
    void parseHourlyForecast(const QJsonArray &hourlyData);
    void parseFiveDayForecast(const QJsonArray &dailyData);
    void parseWeatherAlerts(const QJsonArray &alertsData);
private:
    QLineEdit *locationInput;
    QLabel *weatherLabel;
    QLabel *alertLabel;
    QLabel *hourlyForecastLabel;
    QLabel *uvIndexLabel;
    QLabel *precipitationLabel;
    QLabel *fiveDayForecastLabel;
    QLabel *hourlyLabel;
    QLabel *fiveDayLabel;
    QLabel *temperatureImageLabel;
    QPushButton *weatherButton;
    QPushButton *unitButton;
    QNetworkAccessManager *networkManager;
    const QString apiKey = "3dc6bb0d897aa6a8690f276de7bf11db";
    const QString apiURL = "http://api.openweathermap.org/data/2.5/weather";
    QString currentUnit = "C";
    double currentTemp = 0.0;
    QString currentDescription;
    void updateWeatherLabel();
    double convertTemperature(double temp, const QString &unit);
};

#endif // WEATHERWIDGET_H
