# QTheme Manager

A modern, reusable **QSS theme library** for Qt Widgets applications.  
Provides 7 professionally designed themes, a clean theme management API, and a full-featured demo application.

---

## ✨ Features

- **7 built-in themes** with distinct visual styles
- **ThemeManager** singleton — load, register, and apply themes with one call
- **ThemeRegistry** — structured metadata for building theme picker UIs
- **File-based QSS** — themes live in `.qss` files, easy to edit without recompiling
- **Qt5 & Qt6 compatible** — single CMakeLists.txt handles both
- **Full demo app** — showcases all themes across 6 widget category pages
- **Reusable module** — drop `src/theme/` into any Qt Widgets project

---

## 🎨 Themes

| Key | Display Name | Style |
|-----|-------------|-------|
| `light_minimal` | Light Minimal | Clean SaaS-style light UI |
| `dark_pro` | Dark Pro | Professional IDE/developer dark theme |
| `glass_futuristic` | Glass Futuristic | Sci-fi gradient accents, tech feel |
| `soft_rounded` | Soft Rounded | Warm neutrals, generous rounded corners |
| `high_contrast` | High Contrast | Maximum readability, accessibility-focused |
| `blue_business` | Blue Business | Corporate enterprise blue |
| `green_eye` | Green Eye Care | Low-fatigue green-tinted dark theme |

---

## 🖥️ Widget Coverage

The demo and QSS themes cover:

**Input Controls**
- `QPushButton` (primary, flat, secondary, danger, sizes, states)
- `QToolButton` (normal, checkable, with menu)
- `QCheckBox` (unchecked, checked, tristate, disabled)
- `QRadioButton`
- `QLineEdit` (normal, placeholder, password, read-only, disabled, clear button)
- `QTextEdit` / `QPlainTextEdit`
- `QSpinBox` / `QDoubleSpinBox`
- `QDateEdit` / `QTimeEdit` / `QDateTimeEdit`
- `QComboBox` / `QFontComboBox`
- `QSlider` (horizontal, vertical)
- `QDial`

**Views**
- `QListWidget` / `QListView`
- `QTreeWidget` / `QTreeView`
- `QTableWidget` / `QTableView`
- `QHeaderView`
- `QCalendarWidget`

**Containers**
- `QGroupBox` (standard, checkable, disabled)
- `QTabWidget` / `QTabBar`
- `QToolBox`
- `QSplitter`
- `QFrame` (all shapes)
- `QScrollArea`
- `QStackedWidget`

**Navigation**
- `QMenuBar` / `QMenu`
- `QToolBar`
- `QStatusBar`
- `QDockWidget`

**Feedback / Progress**
- `QProgressBar` (determinate, indeterminate, animated)
- `QScrollBar` (horizontal, vertical)
- `QLabel` (normal, rich text, disabled, link)
- Tooltips (`QToolTip`)

**States covered per widget:**
`normal` · `hover` · `pressed` · `checked` · `disabled` · `focus` · `selected` · `read-only`

---

## 🔨 Build & Run

### Prerequisites

- CMake ≥ 3.16
- Qt 5.15+ **or** Qt 6.x (auto-detected)
- C++17 compiler

### Build steps

```bash
# Clone / open the project
cd qtheme_manager

# Configure
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# Run the demo
./build/QThemeDemo          # Linux/macOS
build\Release\QThemeDemo.exe  # Windows
```

The CMake post-build step automatically copies the `themes/` directory next to the executable.

---

## 🔌 Integrating into Your Qt Project

### Step 1 — Copy the theme module

Copy these files into your project:

```
src/theme/
  ThemeManager.h
  ThemeManager.cpp
  ThemeRegistry.h
  ThemeRegistry.cpp
  themes/
    *.qss
```

### Step 2 — Add to CMakeLists.txt

```cmake
add_library(QThemeLib STATIC
    src/theme/ThemeManager.cpp
    src/theme/ThemeRegistry.cpp
)
target_include_directories(QThemeLib PUBLIC src/theme)
target_link_libraries(QThemeLib PUBLIC Qt6::Core Qt6::Widgets)

target_link_libraries(YourApp PRIVATE QThemeLib)
```

### Step 3 — Initialize at startup

```cpp
#include "ThemeManager.h"
#include "ThemeRegistry.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Register metadata (optional, for UI pickers)
    ThemeRegistry::registerBuiltinThemes();

    // Load all .qss files from a directory
    ThemeManager::instance().initialize("/path/to/themes");

    // Apply a theme
    ThemeManager::instance().applyTheme(&app, "dark_pro");

    // ...
}
```

### Step 4 — Switch themes at runtime

```cpp
// By key
ThemeManager::instance().applyTheme(qApp, "light_minimal");

// List available themes
QStringList themes = ThemeManager::instance().availableThemes();

// Get current theme
QString current = ThemeManager::instance().currentTheme();

// React to theme changes
connect(&ThemeManager::instance(), &ThemeManager::themeChanged,
        this, [](const QString& name) {
    qDebug() << "Theme changed to:" << name;
});
```

---

## ➕ Adding a New Theme

1. Create `src/theme/themes/my_theme.qss`
2. Use any existing `.qss` as a template
3. The theme is auto-discovered by `ThemeManager::initialize()` — no code changes needed
4. Optionally register metadata in `ThemeRegistry::registerBuiltinThemes()`:

```cpp
reg.registerInfo({
    "my_theme",           // key (matches filename without .qss)
    "My Theme",           // display name
    "Description here",   // description
    "light",              // category: "light", "dark", or "special"
    "#FF6600",            // primary color
    "#FFFFFF",            // background color
    "#333333"             // text color
});
```

---

## ⚠️ QSS Limitations

Qt Style Sheets are powerful but have known limitations:

| Feature | Status | Notes |
|---------|--------|-------|
| True blur / frosted glass | ❌ Not supported | Approximated with semi-transparent colors |
| Per-pixel shadows | ❌ Not supported | Use `QGraphicsDropShadowEffect` in C++ |
| CSS animations / transitions | ❌ Not supported | Use `QPropertyAnimation` in C++ |
| `QDial` full styling | ⚠️ Limited | Only background color; needle drawn by Qt |
| `QCalendarWidget` internals | ⚠️ Partial | Navigation bar and cells styled; some sub-widgets need C++ |
| `QMessageBox` icons | ⚠️ Platform-dependent | Standard icons come from the OS |
| `QAbstractScrollArea` corner | ⚠️ Minor | Corner widget between scrollbars may show default style |
| Gradient on `QProgressBar::chunk` | ✅ Supported | Works well |
| Custom `QCheckBox`/`QRadioButton` indicators | ✅ Supported | Use `image:` property with PNG/SVG |

---

## 📁 Project Structure

```
qtheme_manager/
├── CMakeLists.txt
├── README.md
├── resources/
│   └── resources.qrc          # Embeds QSS files as Qt resources
└── src/
    ├── theme/                  # ← Reusable module (copy this to your project)
    │   ├── ThemeManager.h/.cpp
    │   ├── ThemeRegistry.h/.cpp
    │   └── themes/
    │       ├── light_minimal.qss
    │       ├── dark_pro.qss
    │       ├── glass_futuristic.qss
    │       ├── soft_rounded.qss
    │       ├── high_contrast.qss
    │       ├── blue_business.qss
    │       └── green_eye.qss
    └── demo/                   # Demo application
        ├── main.cpp
        ├── MainWindow.h/.cpp
        └── pages/
            ├── ButtonsPage.h/.cpp
            ├── InputsPage.h/.cpp
            ├── ViewsPage.h/.cpp
            ├── ContainersPage.h/.cpp
            ├── NavigationPage.h/.cpp
            └── FeedbackPage.h/.cpp
```

---

## 📸 Screenshots

> *(Switch themes using the toolbar dropdown or the dock panel on the right)*

| Theme | Preview |
|-------|---------|
| Dark Pro | *(run the demo)* |
| Light Minimal | *(run the demo)* |
| Glass Futuristic | *(run the demo)* |
| Soft Rounded | *(run the demo)* |
| High Contrast | *(run the demo)* |
| Blue Business | *(run the demo)* |
| Green Eye Care | *(run the demo)* |

---

## 🚀 Future Improvements

- [ ] Add SVG icon support for checkbox/radio indicators
- [ ] Provide a `ThemeEditor` widget for live QSS editing
- [ ] Add per-widget color token system (CSS variables approximation)
- [ ] Support `.qrc`-embedded themes as primary loading path
- [ ] Add `QWizard` and `QAbstractItemDelegate` styling examples
- [ ] Provide a `ThemePreviewWidget` thumbnail generator
- [ ] Dark/light mode auto-detection from OS settings (Qt 6.5+)

---

## 📄 License

MIT License — free to use in commercial and open-source projects.
