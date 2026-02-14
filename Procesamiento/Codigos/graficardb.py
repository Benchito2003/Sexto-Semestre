import wfdb
import matplotlib.pyplot as plt
import numpy as np

# Nombre del registro
record_name = "100"

# Descargar y leer desde PhysioNet
record = wfdb.rdrecord(record_name, pn_dir="mitdb")

# Frecuencia de muestreo
fs = record.fs

# Extraer señal (canal 0)
signal = record.p_signal[:, 0]

# Tiempo en segundos
t = np.arange(len(signal)) / fs

# Graficar solo 10 segundos
seconds = 10
samples = int(seconds * fs)

plt.figure()
plt.plot(t[:samples], signal[:samples])
plt.xlabel("Tiempo (s)")
plt.ylabel("Voltaje (mV)")
plt.title("MIT-BIH Record 100 - ECG")
plt.show()
