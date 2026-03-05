---
tags:
  - Tema
Materia: "[[MOC-Interfaces|Interfaces Hombre-Maquina]]"
Clases relacionadas:
---
# Como flashear un ESP32 con micropython
==NOTA: Este proceso está adaptado para ser usado desde un entorno base linux (Arch Linux en este caso)==


**Alias útiles a futuro en la terminal:**
```bash
# Gestión de MicroPython
alias esp-flash='esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash -z 0x1000'
alias esp-repl='mpremote connect /dev/ttyUSB0 repl'
alias esp-put='mpremote cp' # Ejemplo: esp-put main.py :main.py

# Gestión de C++ (requiere arduino-cli)
alias esp-compile='arduino-cli compile --fqbn esp32:esp32:esp32'
alias esp-upload='arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:esp32'
```

**Documentación del ESP32 con micropython: ** https://docs.micropython.org/en/latest/esp32/quickref.html

1. Instalar e2sptool: 
```bash
sudo pacman -S esptool
```
2. Entrar a  https://micropython.org/download/ESP32_GENERIC/ y descargar una una versión de binarios.
3. Conectar el ESP32
4. Borrar el ESP32:
   ```bash
   esptool --port /dev/ttyUSB0 erase-flash
   ```
5. Flashear el ESP32 con los binarios descargados:
```bash
esptool --port /dev/ttyUSB0 --chip esp32 write-flash -z 0x1000 nombre_de_tu_firmware.bin
```

