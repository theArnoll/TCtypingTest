# Traditional Chinese typing test

There are a lot of Engish typing tests online, like my personal favorite [Monkeytype](https://monkeytype.com/) that has the best UI and UX in my opinion, [Mitype](https://github.com/Mithil467/mitype) that has very complete function and is even close to the CLI version of Monkeytype at least for me, and [10FastFingers](https://10fastfingers.com), which has online competitions, and much more. However, there are no typing tests for Traditional Chinese that's good enough and able to reflect the real-world typing speed and support the most common input methods well enough and actually close to the typing habit of native users and eve the language itself. So I decided to make my own typing test for Traditional Chinese, which is a console application written in C++.

This is what this fixed compare to other typing tests that I have seen

| Original | Problem | Fixes |
|----------|---------|-------|
| [Monkeytype](https://monkeytype.com/) | Adding spaces between words when Chinese is actually not using spaces | No spaces between words |
| [Typing.tw](https://typing.tw/) | Selecting old paragraph that containing a lot of words and phrasing, and even the nuanced grammar (in some paragraphs) that's not commonly used in modern writing anymore | Writing new paragraphs that are more modern and commonly used in modern world |
| [Mitype](https://github.com/Mithil467/mitype) | Only support English. Althought it's able to use the content of your own file as the sample, it's not able to exclude the trailing input code of your input method. | Well this test IS in Chinese.<br>The trailing input code is planned to try fixing in the future, although I'm not planned to add a countdown mode by myself |

However, this also have some cons:
- The test is not online, so you have to download and run it on your own computer
- There are no count-down timer mode so you'll have to type the whole sentences. You can only choose the length of the test
  - For this, I want to mention that [Mitype](https://github.com/Mithil467/mitype) done a great job on this

## Usage

### First run

Binary isn't available at least yet, so you'll have to compile it yourself.

#### Windows

1. Open terminal in the folder where you extracted the source code and run:
    ```bash
    g++ -std=c++23 main.cpp -o main.exe
    ```
2. Double click the `main.exe` file to run the program

#### Linux / macOS

Open terminal in the folder where you extracted the source code and run `build.sh`:

```bash
chmod +x ./build.sh
./build.sh
```

The program will start automtically after the compilation is done.

To run the program afterward, open terminal in the folder where you store the binary and run:

```bash
./main.out
```

### In the program

1. You'll be asked to choose the length of the test. You can type your selection in both English alphabet or Chinese chararcter according to the instruction in parentheses and press enter.
2. The first two characters of the test will be shown in the first line as a preview. Press Enter to expand the whole sentence / paragraph **and** start the test.
3. Type the sentence / paragraph shown and press Enter to submit your input.
4. The program will show your typing speed and accuracy after you submit your input. You can choose to do another test, change length or exit the program.
   - If you choose to do another test, it won't ask you to choose the length again, It'll start another test in the length you've chosen previously.

All the operations and options are wrote in the instruction in the parentheses.

### Operation "screen shot"s

```
請輸入你想要測驗的長度 (s / m / l / 短 / 中 / 長 / q / 離): s
```

```
準備好後按下 Enter 鍵
鍵盤
```

```
準備好後按下 Enter 鍵
鍵盤敲擊聲很清脆
鍵盤敲擊聲很
```

```
鍵盤敲擊聲很清脆
鍵盤敲擊聲很清脆
                
花費時間: 5.84 秒
|>> 82.25 CPM <<|

總字數: 8 | 正確字數: 8 | 錯誤字數: 0 | 正確率: 100.00%

再來一次?
r / 再 / 在: 再來一次   s / 設: 進入設置        q / 離: 離開
 > 
```

```
鍵盤敲擊聲很清脆
鍵盤敲擊聲很清脆
                
花費時間: 5.84 秒
|>> 82.25 CPM <<|

總字數: 8 | 正確字數: 8 | 錯誤字數: 0 | 正確率: 100.00%

再來一次?
r / 再 / 在: 再來一次   s / 設: 進入設置        q / 離: 離開
 > s
請輸入你想要測驗的長度 (s / m / l / 短 / 中 / 長 / q / 離): m
```

```
傍晚的天空被夕陽染成金黃色讓人感到無比放鬆與平靜
傍晚的天空被夕陽染從金黃色讓人感到無比放鬆平靜
                   ͯ                        ͯ  ͯ |
花費時間: 27.74 秒
|>> 43.26 CPM <<|
49.75 CPM (RAW)
總字數: 24 | 正確字數: 20 | 錯誤字數: 4 | 正確率: 83.33%

再來一次?
r / 再 / 在: 再來一次   s / 設: 進入設置        q / 離: 離開
 > 再
```

```
練習打字需要持之以恆每天進步一點點就能看到成果
練習打字需要持之以恆每天進步一點點點就能看到成果了
                                   ͯ  ͯ  ͯ  ͯ  ͯ  ͯ 
花費時間: 16.37 秒
|>> 62.30 CPM <<|
91.62 CPM (RAW)
總字數: 23 | 正確字數: 17 | 錯誤字數: 6 | 正確率: 73.91%

再來一次?
r / 再 / 在: 再來一次   s / 設: 進入設置        q / 離: 離開
 > 離
```

## Third-party libraries (kinda?)

[My mulsys header](https://github.io/theArnoll/mulsys.h)

## Tested on

- Windows 11
- Ubuntu Server 24.04

## To do

- [ ] Expand test strings
- [ ] Make test strings an external file
- [ ] Add longer test strings
- [ ] Add more detailed length options
- [ ] At least try dealing with trailing Zhuyins and Pinyins in the input
- [ ] Save results to CSV file

## AI usage
