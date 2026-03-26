# QTheme Manager

A modern, reusable **QSS theme library** for Qt Widgets applications, distributed as a **shared library (DLL / .so / .dylib)**.  
Provides 7 professionally designed themes, a clean theme management API, and an optional full-featured demo application.

All themes and icon assets are **compiled into the library** as Qt resources — no external files are needed at runtime.

---

## ✨ Features

- **7 built-in themes** with distinct visual styles
- **ThemeManager** singleton — load, register, and apply themes with one call
- **ThemeRegistry** — structured metadata for building theme picker UIs
- **Embedded resources** — QSS files and SVG icons compiled into `QThemeLib.dll` (no loose files at runtime)
- **Qt5 & Qt6 compatible** — single CMakeLists.txt handles both
- **Submodule-friendly** — set `QTHEME_BUILD_DEMO=OFF` to build only the library
- **Full demo app** — showcases all themes across 6 widget category pages

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

### Build steps (standalone)

```bash
# Clone the project
cd qtheme_manager

# Configure — builds QThemeLib.dll + QThemeDemo by default
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# Run the demo
./build/QThemeDemo          # Linux/macOS
build\QThemeDemo.exe        # Windows (QThemeLib.dll is copied automatically)
```

### Build only the library (no demo)

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DQTHEME_BUILD_DEMO=OFF
cmake --build build --config Release
```

---

## 🔌 Using as a Git Submodule

### Step 1 — Add the submodule

```bash
git submodule add https://github.com/junliangdg/qtheme_manager.git third_party/qtheme_manager
git submodule update --init
```

### Step 2 — Add to your CMakeLists.txt

```cmake
# Build only the DLL, skip the demo
add_subdirectory(third_party/qtheme_manager EXCLUDE_FROM_ALL)
set(QTHEME_BUILD_DEMO OFF CACHE BOOL "" FORCE)

# Link your application against QThemeLib
target_link_libraries(YourApp PRIVATE QThemeLib)
```

> **Note:** `QTHEME_BUILD_DEMO` must be set **before** `add_subdirectory`, or use the `CACHE … FORCE` form shown above.

### Step 3 — Initialize at startup

```cpp
#include "ThemeManager.h"
#include "ThemeRegistry.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Register metadata (optional, for UI pickers)
    ThemeRegistry::registerBuiltinThemes();

    // Load all themes embedded in QThemeLib (:/themes/)
    ThemeManager::instance().initialize();

    // Apply a theme
    ThemeManager::instance().applyTheme(&app, "dark_pro");

    // ...
}
```

No `.qss` files need to be copied — everything is embedded in the DLL.

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

## 🔌 Integrating without Git Submodule (copy-in)

If you prefer to copy the source directly:

### Step 1 — Copy the theme module

```
src/theme/
  qthemelib_global.h
  ThemeManager.h / .cpp
  ThemeRegistry.h / .cpp
  qthemelib_resources.qrc   ← embeds QSS + icons
  themes/
    *.qss
resources/
  icons/
    *.svg
```

### Step 2 — Add to CMakeLists.txt

```cmake
add_library(QThemeLib SHARED
    src/theme/ThemeManager.cpp
    src/theme/ThemeRegistry.cpp
    src/theme/qthemelib_resources.qrc
)
target_compile_definitions(QThemeLib PRIVATE QTHEMELIB_LIBRARY)
target_include_directories(QThemeLib PUBLIC src/theme)
target_link_libraries(QThemeLib PUBLIC Qt6::Core Qt6::Widgets)

target_link_libraries(YourApp PRIVATE QThemeLib)
```

---

## ➕ Adding a New Theme

1. Create `src/theme/themes/my_theme.qss`
2. Add it to `src/theme/qthemelib_resources.qrc`:
   ```xml
   <file alias="my_theme.qss">themes/my_theme.qss</file>
   ```
3. The theme is auto-discovered by `ThemeManager::initialize()` — no other code changes needed
4. Optionally register metadata in `ThemeRegistry::registerBuiltinThemes()`:

```cpp
reg.registerInfo({
    "my_theme",           // key (matches alias without .qss)
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
├── build_debug.bat
├── resources/
│   └── icons/                  # SVG icons (referenced by qthemelib_resources.qrc)
│       └── *.svg
└── src/
    ├── theme/                  # ← QThemeLib shared library
    │   ├── qthemelib_global.h  # DLL export/import macro
    │   ├── ThemeManager.h/.cpp
    │   ├── ThemeRegistry.h/.cpp
    │   ├── qthemelib_resources.qrc  # Embeds QSS + icons into the DLL
    │   └── themes/
    │       ├── light_minimal.qss
    │       ├── dark_pro.qss
    │       ├── glass_futuristic.qss
    │       ├── soft_rounded.qss
    │       ├── high_contrast.qss
    │       ├── blue_business.qss
    │       └── green_eye.qss
    └── demo/                   # Optional demo application (QTHEME_BUILD_DEMO=ON)
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
| Dark Pro | <a href="./docs/images/dark-pro.jpg"><img src="./docs/images/dark-pro.jpg" alt="Dark Pro" width="260" /></a> |
| Light Minimal | <a href="./docs/images/light-minimal.jpg"><img src="./docs/images/light-minimal.jpg" alt="Light Minimal" width="260" /></a> |
| Glass Futuristic | <a href="./docs/images/glass-futuristic.jpg"><img src="./docs/images/glass-futuristic.jpg" alt="Glass Futuristic" width="260" /></a> |
| Soft Rounded | <a href="./docs/images/soft-rounded.jpg"><img src="./docs/images/soft-rounded.jpg" alt="Soft Rounded" width="260" /></a> |
| High Contrast | <a href="./docs/images/high-contrast.jpg"><img src="./docs/images/high-contrast.jpg" alt="High Contrast" width="260" /></a> |
| Blue Business | <a href="./docs/images/blue-business.jpg"><img src="./docs/images/blue-business.jpg" alt="Blue Business" width="260" /></a> |
| Green Eye Care | <a href="./docs/images/green-eye-care.jpg"><img src="./docs/images/green-eye-care.jpg" alt="Green Eye Care" width="260" /></a> |

---

## 🚀 Future Improvements

- [ ] Add SVG icon support for checkbox/radio indicators
- [ ] Provide a `ThemeEditor` widget for live QSS editing
- [ ] Add per-widget color token system (CSS variables approximation)
- [ ] Add `QWizard` and `QAbstractItemDelegate` styling examples
- [ ] Provide a `ThemePreviewWidget` thumbnail generator
- [ ] Dark/light mode auto-detection from OS settings (Qt 6.5+)

---

## 📄 License

MIT License — free to use in commercial and open-source projects.
