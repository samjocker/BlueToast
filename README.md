# 如何使用Ios設備控制藍牙開發板
本文章使用esp32作為範例
## 方法
1. 將上方blueToastDemo資料夾下載並開啟
2. 到例如 https://www.uuidgenerator.net/  之類的UUID生成網站產生一份UUID，並將此行UUID替換掉
```c=14
#define myUuid "aaaaaaae-aaaa-aaaa-aaaa-aaaaaaaaaaaa"
```
3. 測試腳位為15，可自行更改
```c=12
#define testPin 15 // 測試腳位
```
4. 於Ios設備顯示之名稱，預設為"espDevice"，可自行更改
```c=54
BLEDevice::init("espDevice");
```
5. 撰寫自己所需功能程式，範例為開關燈範例程式，stringValue為藍牙接收到之指令(可在後續於App自定義)
```c=75
  // ----------------- ↓ 自定義功能區↓  -----------------
  // 以下為開燈範例，請自己撰寫所需功能
	if (stringValue == "lightOn") {
	  digitalWrite(testPin, 1);
  } else if (stringValue == "lightOff") {
	  digitalWrite(testPin, 0);
	}
  // ----------------- ↑ 自定義功能區↑  -----------------
```
6. 將程式燒入進開發板內
7. 至App Store下載 [不如吐司](https://apps.apple.com/tw/app/%E4%B8%8D%E5%A6%82%E5%90%90%E5%8F%B8/id6502551318)App

    <img src="image/appPreview.jpeg" width="150">

8. 授權藍牙權限

    <img src="image/bleAuthorization.PNG" width="150">

9. 如果順利的話應該開啟後就會找到你取的裝置名稱

    <img src="image/deviceList.PNG" width="150">

10. 連接裝置後可以點擊右上角加號新增自訂按鈕，編輯頁面最下方輸入指令區為設定藍牙傳送之字串，按下按鈕後即發送此串字串，而同時開發板程式中的stringValue變數會變為接收到之字串。

    圖標庫是使用蘋果系統內建的[SF Symbols](https://developer.apple.com/sf-symbols/)所以搜尋時需使用英文名稱搜尋，此圖標庫有5000多個圖標，若找不到理想icon時可以多換關鍵字搜尋，例如燈相關可以搜尋"light"之類的單字。

<img src="image/editPage.jpeg" width="150">

11. 想要刪除或編輯按鈕的話長按按鈕即可叫出選單選擇

<img src="image/contentButton.PNG" width="150">