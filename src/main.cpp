#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "CTBot.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define buzzer D3
#define ONE_WIRE_BUS D4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
CTBot myBot;

String ssid = "malang.com";    //nama ssid wifi kalian
String pass = "akardari9";  //password wifi kalian
String token = "5623397861:AAHBvLs-NFi5r0mEQYN1MNtxGOkaydDbSxs";    //token bot baru kalian
const int id = 1483096382;      //id telegram kalian

void buzzerNyala();

void setup(void)
{
  Serial.begin(9600);
  sensors.begin(); //memulai baca sensor
  lcd.init(); //memulai LCD
  lcd.backlight(); //menyalakan Lampu latar belakang LCD
  pinMode(buzzer, OUTPUT); //inisialisasi buzzer sebagai output
  myBot.wifiConnect(ssid, pass); //koneksi dengan hotspot
  myBot.setTelegramToken(token); //memastikan token

  //tes koneksi dengan hotspot
  if (myBot.testConnection()) {
    Serial.println("Koneksi Bagus");
  } else {
    Serial.println("Koneksi Jelek");
  }
}

void loop(void)
{ 
  sensors.requestTemperatures(); //baca sensor
  int suhu = sensors.getTempCByIndex(0);
  //Penulisan suhu pada LCD dan serial monitor
  Serial.println(suhu);

  //Jika suhu lebih dari 30
  if (suhu > 30) {
    myBot.sendMessage(id, "Suhu Akuarium Terlalu Panas!"); //mengirimkan pesan ke telegram
    buzzerNyala(); //menyalakan buzzer
    lcd.setCursor(0,0);
    lcd.print("SUHU PANAS!"); //menampilkan SUHU PANAS di LCD
    }

  else if (suhu < 25) {
    myBot.sendMessage(id, "Suhu Akuarium Terlalu Dingin!"); //mengirimkan pesan ke telegram
    buzzerNyala(); //menyalakan buzzer
    lcd.setCursor(0,0);
    lcd.print("SUHU DINGIN!"); //menampilkan SUHU DINGIN di LCD
  }
  else {
    digitalWrite(buzzer, LOW);
    lcd.setCursor(0,0);
    lcd.print("Suhu air : ");
    lcd.setCursor(0,1);
    lcd.print(suhu);
  }
  lcd.clear();
}

void buzzerNyala(){ //Function untuk menyalakan buzzer
  digitalWrite(buzzer, HIGH);
  delay (500);
  digitalWrite(buzzer, LOW);
  delay (500);
}
