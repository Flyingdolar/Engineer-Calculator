# Engineer_Calculator

> Contributed by Flyingdollar

## 下載與安裝

> 須在 Linux 環境下執行，目前僅測試過 Ubuntu 20.04 LTS上運行正常

1. 在 Github 上下載專案：點擊 Code -> Download ZIP
2. 解壓縮專案
3. 在專案目錄下執行 `make` 指令
4. 執行 `./calculator` 即可使用

## 使用與參數說明

分為兩種模式：寫入檔案運算與直接運算

### A. 寫入檔案運算

> 運算結果會寫入檔案中

1. 執行 `./calculator -i <input_file> -o <output_file>`
2. 檔案格式為 `*.txt`
3. 運算之前，須先定義所有變數
4. 範例格式如下：

    ```txt
    int ant, bee, car; // integer variables
    float digit, e ; // float variables

    ant =  5 ;
    bee =7 ;
    car = log (12 +23) / log[3] 5 +(ant + 12)* (bee + 8);
    digit = car + 1.2 + sin 45;
    e = digit + bee * 5.6;
    ```

5. 運算結果會寫入 `output_file` 中
6. 相關規範
   1. 變數名稱與 C++ 變數命名規則大致相同
   2. 變數宣告需要指定型別
   3. 多餘的空白字元是允許的
   4. 註解部分需要以 `//` 註明，程式便會忽略該符號後面的內容

### B. 直接運算

> 運算結果會直接顯示在螢幕上

1. 執行 `./calculator -d`
2. 會出現 `>>>` 提示符號如下，此時輸入你要運算的內容即可（不可以有等號）

    ```bash
    $./calculator -d                                                                                                                           ─╯
    Please input the expression you want to calculate.
    >>> 100 + log 2
    Result: 100.301
    ```

### C. 協助

如果忘記指令，可以輸入 `./calculator -h` 來查看幫助訊息

## 支援的功能與參數

| 符號 | 功能說明 |
| --- | --- |
| () | 括號：`(a + b) * c` |
| \+ | 加法：`a + b` |
| \- | 減法：`a - b` |
| \* | 乘法：`a * b` |
| / | 除法：`a / b` |
| ^ | 次方：`a ^ b` |
| mod | 取餘數：`a mod b` |
| log | 對數：`log a` （預設為 log\[10\] a ，可指定底數： log\[b\] a） |
| exp | 自然對數指數：`exp a` |
| sqrt | 次方根：`sqrt a` （預設為 sqrt\[2\] a ，可指定底數： sqrt\[b\] a） |
| sin | 正弦：`sin a` （可以輸入 sin\[-1\] a 來計算反正弦） |
| cos | 餘弦：`cos a` （可以輸入 cos\[-1\] a 來計算反餘弦） |
| tan | 正切：`tan a` （可以輸入 tan\[-1\] a 來計算反正切） |
