# C++ Vision Monitor

C++の設計、ビルド、テスト、画像処理、AI推論を段階的に学ぶための画像認識アプリケーションです。

画像ファイルやWebカメラから入力を取得し、前処理、AI推論、結果表示、ログ保存までの一連のパイプラインを構築します。

最初はダミー推論を使ったシンプルなCLIアプリとして実装し、最終的にはOpenCVとONNX Runtimeを利用したリアルタイム画像認識アプリへ発展させます。

---

## 目的

本プロジェクトの目的は、C++の文法を個別に学ぶだけではなく、実際のアプリケーション開発を通して以下を身につけることです。

- モダンC++の基本的な設計
- クラスの責務分離
- RAIIとオブジェクトの寿命管理
- スマートポインタ
- STLコンテナとアルゴリズム
- 例外処理とエラー処理
- ヘッダーとソースファイルの分割
- CMakeによるビルド管理
- 単体テスト
- OpenCVによる画像処理
- ONNX RuntimeによるAI推論
- 並行処理
- パフォーマンス計測

---

## 完成イメージ

```text
画像ファイル・Webカメラ
          ↓
      ImageLoader
          ↓
   ImagePreprocessor
          ↓
    InferenceEngine
          ↓
    ResultProcessor
       ↓         ↓
 ConsoleView   ResultLogger
```

---

## 主な機能

### 初期バージョン

- [ ] 画像パスをコマンドライン引数から受け取る
- [ ] 入力されたパスを検証する
- [ ] ダミーの推論結果を生成する
- [ ] 推論結果をコンソールへ表示する
- [ ] 推論結果をCSVファイルへ保存する
- [ ] CMakeでビルドする
- [ ] 基本処理の単体テストを作成する

### 画像処理対応

- [ ] OpenCVで画像を読み込む
- [ ] 画像サイズを取得する
- [ ] 画像を指定サイズへリサイズする
- [ ] BGRからRGBへ変換する
- [ ] 画素値を正規化する
- [ ] 前処理済み画像を保存する

### AI推論対応

- [ ] ONNXモデルを読み込む
- [ ] モデルの入力shapeを取得する
- [ ] 入力テンソルを生成する
- [ ] ONNX Runtimeで推論する
- [ ] 出力テンソルを解析する
- [ ] 上位の推論結果を表示する
- [ ] 信頼度によるフィルタリングを行う

### 発展機能

- [ ] Webカメラから映像を取得する
- [ ] フレームごとに推論する
- [ ] 推論時間を計測する
- [ ] FPSを表示する
- [ ] 推論処理を別スレッドで実行する
- [ ] CPU推論とGPU推論を比較する
- [ ] 設定ファイルから閾値を変更する
- [ ] GUIを追加する

---

## 使用予定の技術

- C++17以上
- CMake
- OpenCV
- ONNX Runtime
- GoogleTest
- AddressSanitizer
- UndefinedBehaviorSanitizer

将来的には、以下の利用も検討します。

- CUDA
- TensorRT
- spdlog
- JSON設定ファイル
- GitHub Actions

---

## ディレクトリ構成

```text
cpp-vision-monitor/
├── CMakeLists.txt
├── README.md
├── app/
│   └── main.cpp
├── include/
│   ├── Application.h
│   ├── DetectionResult.h
│   ├── IInferenceEngine.h
│   ├── DummyInferenceEngine.h
│   ├── ImageLoader.h
│   ├── ResultProcessor.h
│   └── ResultLogger.h
├── src/
│   ├── Application.cpp
│   ├── DummyInferenceEngine.cpp
│   ├── ImageLoader.cpp
│   ├── ResultProcessor.cpp
│   └── ResultLogger.cpp
├── tests/
│   ├── CMakeLists.txt
│   └── ResultProcessorTest.cpp
├── config/
├── models/
├── resources/
└── output/
```

### 各ディレクトリの役割

```text
app/
    アプリケーションのエントリーポイント

include/
    クラスと関数の宣言

src/
    クラスと関数の実装

tests/
    単体テスト

config/
    設定ファイル

models/
    ONNXモデル

resources/
    入力画像などのテストデータ

output/
    推論結果やログの出力先
```

---

## クラス構成

### `Application`

アプリケーション全体の進行を管理します。

```text
入力取得
前処理
推論
結果処理
表示
保存
```

個別処理の詳細は、ほかのクラスへ委譲します。

### `IInferenceEngine`

推論処理のインターフェースです。

```cpp
class IInferenceEngine
{
public:
    virtual ~IInferenceEngine() = default;

    virtual std::vector<DetectionResult> infer(
        const std::string& imagePath
    ) = 0;
};
```

### `DummyInferenceEngine`

開発初期に使用するダミー推論エンジンです。

ONNX Runtimeを導入する前に、アプリケーション全体の設計と処理フローを確認するために使用します。

### `OnnxInferenceEngine`

将来的に追加するONNX Runtime用の推論エンジンです。

`IInferenceEngine` を継承することで、ダミー推論からONNX推論へ差し替えられる設計を目指します。

### `DetectionResult`

推論結果を表します。

```cpp
struct DetectionResult
{
    std::string label;
    float confidence;
};
```

### `ResultProcessor`

以下の処理を担当します。

- 信頼度によるフィルタリング
- 信頼度順の並べ替え
- 最も信頼度が高い結果の取得
- 上位N件の抽出

### `ResultLogger`

推論結果をCSVファイルなどへ保存します。

---

## 設計方針

### 責務を分離する

各クラスが担当する仕事を明確にします。

```text
画像を読み込む
→ ImageLoader

画像を前処理する
→ ImagePreprocessor

推論する
→ InferenceEngine

推論結果を整理する
→ ResultProcessor

画面に表示する
→ ConsoleView

ファイルへ保存する
→ ResultLogger
```

### 所有権を明確にする

原則として、所有者が1つの場合は `std::unique_ptr` を使用します。

```cpp
std::unique_ptr<IInferenceEngine> inferenceEngine;
```

複数所有が本当に必要な場合に限り、`std::shared_ptr` を検討します。

### AI推論処理を差し替え可能にする

アプリケーションが特定の推論ライブラリへ直接依存しないようにします。

```text
Application
    ↓
IInferenceEngine
    ├── DummyInferenceEngine
    ├── OnnxInferenceEngine
    └── TensorRtInferenceEngine
```

---

## ビルド方法

### 必要環境

初期バージョンでは、以下が必要です。

- C++17対応コンパイラ
- CMake 3.15以上

バージョン確認：

```bash
cmake --version
```

```bash
g++ --version
```

### CMakeの設定

リポジトリのルートディレクトリで実行します。

```bash
cmake -S . -B build
```

### ビルド

```bash
cmake --build build
```

### 実行

Linux、macOS、WSLの場合：

```bash
./build/VisionMonitor
```

WindowsでVisual Studio Generatorを使用する場合：

```powershell
.\build\Debug\VisionMonitor.exe
```

---

## 実行イメージ

```bash
./build/VisionMonitor resources/sample.jpg
```

出力例：

```text
Input image: resources/sample.jpg

Inference results:
1. cat: 0.95
2. tiger: 0.03
3. dog: 0.02

Inference time: 12 ms
Result saved to: output/results.csv
```

初期バージョンでは、実際のAI推論ではなく固定のダミーデータを表示します。

---

## CMake構成案

初期段階では、アプリケーション本体とコア処理を分離します。

```cmake
cmake_minimum_required(VERSION 3.15)

project(
    CppVisionMonitor
    VERSION 0.1.0
    LANGUAGES CXX
)

add_library(
    VisionCore
    src/Application.cpp
    src/DummyInferenceEngine.cpp
    src/ResultProcessor.cpp
    src/ResultLogger.cpp
)

target_include_directories(
    VisionCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
    VisionCore
    PUBLIC cxx_std_17
)

add_executable(
    VisionMonitor
    app/main.cpp
)

target_link_libraries(
    VisionMonitor
    PRIVATE VisionCore
)
```

---

## 開発ロードマップ

### Phase 1：C++アプリケーションの土台

目標は、外部ライブラリを使わずにアプリケーション全体を完成させることです。

- CMakeプロジェクトの作成
- クラスとファイルの分割
- ダミー推論エンジンの実装
- 結果の表示
- CSVへの保存
- 例外処理
- 単体テスト

### Phase 2：OpenCVの導入

- OpenCVをCMakeからリンク
- 画像ファイルの読み込み
- 画像のリサイズ
- 色変換
- 正規化
- 前処理クラスのテスト

### Phase 3：ONNX Runtimeの導入

- ONNXモデルの読み込み
- 入出力情報の取得
- テンソル生成
- 推論実行
- 推論結果の解析
- ダミー推論との切り替え

### Phase 4：リアルタイム化

- Webカメラ入力
- 継続的なフレーム処理
- 推論時間とFPSの計測
- スレッドセーフなキュー
- 推論処理の別スレッド化

### Phase 5：最適化

- CPU使用率の確認
- メモリ使用量の確認
- 不要な画像コピーの削減
- CPU推論とGPU推論の比較
- プロファイリング
- Releaseビルドの比較

---

## テスト方針

AIモデルの精度だけでなく、周辺処理を個別にテストします。

テスト対象の例：

- 信頼度順に並べ替えられること
- 指定した閾値未満の結果が除外されること
- 結果が空の場合を処理できること
- 存在しない画像パスを検出できること
- CSVが正しい形式で出力されること
- 前処理後の画像サイズが正しいこと

---

## 学習テーマ

本プロジェクトでは、機能追加と合わせて以下を学習します。

### C++言語機能

- `const`
- 参照
- RAII
- コピーとムーブ
- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`
- `std::optional`
- `std::variant`
- ラムダ式
- コールバック
- 例外処理

### STL

- `std::vector`
- `std::string`
- `std::unordered_map`
- `std::filesystem`
- `std::sort`
- `std::find_if`
- `std::remove_if`
- `std::transform`

### 開発技術

- CMake
- Git
- 単体テスト
- デバッガ
- Sanitizer
- ログ
- マルチスレッド
- プロファイリング

---

## 現在のステータス

現在はPhase 1の設計・実装段階です。

最初の目標は、ダミー推論を使用して以下の処理を完成させることです。

```text
画像パスの入力
    ↓
ダミー推論
    ↓
信頼度順に並べ替え
    ↓
コンソール表示
    ↓
CSV保存
```

---

## ライセンス

学習用プロジェクトです。

ライセンスは、プロジェクト公開時に決定します。
