#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
String stringValue = "";
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t value[2];
#define testPin 15 // 測試腳位
// ↓ 請至 https://www.uuidgenerator.net/ 自行產生一組 UUID
#define myUuid "aaaaaaae-aaaa-aaaa-aaaa-aaaaaaaaaaaa"
// 	↑請將上方字串更換為自己的 UUID
#define service_uuid myUuid
#define rx_uuid myUuid
#define tx_uuid myUuid

class MyServerCallbacks: public BLEServerCallbacks{
  void onConnect(BLEServer* pServer){
    deviceConnected = true;
  };
  void onDisconnect(BLEServer* pServer){
    deviceConnected = false;
    }
};
String values(uint8_t value) {
  char hex[2];
  sprintf(hex, "%02X", value);
  return hex;
};

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();
    if (rxValue.length() >0) {
      String allValues = "";
      String stringValues = "";
      for(int i=0; i<rxValue.length(); i++) allValues += values(rxValue[i]);
      for(int i=0; i<rxValue.length(); i++) stringValues += rxValue[i];
      Serial.println(allValues);
      Serial.println(stringValues);
      value[0] = rxValue[0];
      value[1] = rxValue[1];
    }
  }
};


void setup() {
  pinMode(testPin, OUTPUT);
  Serial.begin(115200);
  // 裝置名稱↓ 
  BLEDevice::init("espDevice");
  // 裝置名稱↑
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(service_uuid);
  pTxCharacteristic = pService->createCharacteristic(tx_uuid, BLECharacteristic::PROPERTY_NOTIFY);
  pTxCharacteristic->addDescriptor(new BLE2902());
  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(rx_uuid, BLECharacteristic::PROPERTY_WRITE);
  pRxCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("waiting a client connection to notify...");
}

void loop(){
  if(deviceConnected) {
    pTxCharacteristic->setValue((uint8_t*)&value, sizeof(value));
    pTxCharacteristic->notify();
		delay(10);
	}
  // ----------------- ↓ 自定義功能區↓  -----------------
  // 以下為開燈範例，請自己撰寫所需功能
	if (stringValue == "lightOn") {
	  digitalWrite(testPin, 1);
  } else if (stringValue == "lightOff") {
	  digitalWrite(testPin, 0);
	}
  // ----------------- ↑ 自定義功能區↑  -----------------
 
	if (!deviceConnected && oldDeviceConnected) {
	  delay(500);
	  pServer->startAdvertising();
	  Serial.println("start advertising");
	  oldDeviceConnected = deviceConnected;
	}
	if (deviceConnected && !oldDeviceConnected) {
	  oldDeviceConnected = deviceConnected;
	}
}
