# EQ-6S Plugin - Windows Compilation Guide

Esta guía te ayudará a compilar el plugin EQ-6S en Windows para obtener los archivos .dll (VST2) y .vst3 (VST3) que puedes usar en tu DAW.

## 📋 Requisitos Previos

### 1. Visual Studio 2022 Community (GRATIS)
- Descarga desde: https://visualstudio.microsoft.com/vs/community/
- Durante la instalación, selecciona:
  - ✅ **Desarrollo para el escritorio con C++**
  - ✅ **CMake tools for Visual Studio**
  - ✅ **Windows 10/11 SDK** (la versión más reciente)

### 2. CMake (GRATIS)
- Descarga desde: https://cmake.org/download/
- Selecciona "Windows x64 Installer"
- Durante la instalación: ✅ **Add CMake to system PATH**

### 3. JUCE Framework 7.0.12
- Descarga desde: https://github.com/juce-framework/JUCE/releases/tag/7.0.12
- Busca: `juce-7.0.12-windows.zip`
- Descarga y extrae en `C:\JUCE\` (o donde prefieras)

## 🚀 Pasos de Compilación

### Paso 1: Preparar el Proyecto
1. **Extrae el ZIP** del plugin EQ-6S en una carpeta, por ejemplo: `C:\EQ6S-Plugin\`
2. **Crea la carpeta JUCE**: Dentro de `C:\EQ6S-Plugin\`, crea una carpeta llamada `juce-framework`
3. **Copia JUCE**: Copia TODO el contenido de la carpeta JUCE descargada dentro de `juce-framework`

Tu estructura debe verse así:
```
C:\EQ6S-Plugin\
├── Source\
│   ├── PluginProcessor.cpp
│   ├── PluginProcessor.h
│   ├── PluginEditor.cpp
│   └── PluginEditor.h
├── juce-framework\
│   ├── modules\
│   ├── extras\
│   └── CMakeLists.txt
├── CMakeLists.txt
└── .github\
```

### Paso 2: Abrir Command Prompt
1. Presiona `Win + R`, escribe `cmd` y presiona Enter
2. Navega a tu carpeta del proyecto:
```cmd
cd C:\EQ6S-Plugin
```

### Paso 3: Configurar CMake
```cmd
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
```

### Paso 4: Compilar el Plugin
```cmd
cmake --build . --config Release
```

## 📁 Ubicación de los Archivos Compilados

Después de la compilación exitosa, encontrarás los plugins en:

### VST3 Plugin:
```
C:\EQ6S-Plugin\build\EQ6S_artefacts\Release\VST3\EQ-6S.vst3\
```

### Standalone Application:
```
C:\EQ6S-Plugin\build\EQ6S_artefacts\Release\Standalone\EQ-6S.exe
```

## 🎛️ Instalación en tu DAW

### Para VST3:
1. **Copia la carpeta completa** `EQ-6S.vst3` 
2. **Pégala en**: `C:\Program Files\Common Files\VST3\`
3. **Reinicia tu DAW** y busca "EQ-6S" en la lista de plugins

### Para probar:
- **Ejecuta directamente**: `EQ-6S.exe` para probar el plugin standalone
- **Carga en DAW**: Busca "EQ-6S" en la categoría de efectos/EQ

## 🔧 Solución de Problemas

### Error: "CMake not found"
- Reinstala CMake y asegúrate de marcar "Add to PATH"
- Reinicia Command Prompt

### Error: "Visual Studio not found"
- Asegúrate de instalar "Desarrollo para el escritorio con C++"
- Usa el "Developer Command Prompt for VS 2022"

### Error: "JUCE not found"
- Verifica que `juce-framework\CMakeLists.txt` existe
- La estructura de carpetas debe ser exacta

### Error durante compilación:
- Abre el proyecto en Visual Studio:
```cmd
start EQ6S.sln
```
- Compila desde Visual Studio (Build → Build Solution)

## ✅ Verificación

Una vez instalado correctamente:
1. **Abre tu DAW** (Reaper, FL Studio, Ableton, etc.)
2. **Busca "EQ-6S"** en la lista de plugins
3. **Carga el plugin** en una pista de audio
4. **Deberías ver**: Interfaz con textura de madera oscura y 6 bandas de EQ

## 🎵 Características del Plugin

- **6 Bandas de EQ**: Frecuencias ajustables con ganancia ±8dB
- **Saturación Armónica**: Calidez analógica automática
- **Filtros HPF/LPF**: Cortes de 24dB/octava
- **Interfaz Profesional**: Inspirada en hardware de alta gama

¡Disfruta tu nuevo plugin EQ-6S! 🎧
