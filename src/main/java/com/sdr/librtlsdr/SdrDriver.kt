package com.sdr.librtlsdr

class SdrDriver {
    
    companion object {
        init {
            System.loadLibrary("rtlsdr")
        }
    }
    
    external fun getDeviceCount(): Int
    external fun getDeviceName(index: Int): String
    external fun openDevice(index: Int): Int
    external fun closeDevice(): Int
    
    fun detectDevices(): String {
        val count = getDeviceCount()
        return if (count > 0) {
            val name = getDeviceName(0)
            "✅ SDR Detectado!\nDispositivos: $count\nNombre: $name"
        } else {
            "❌ No se detectaron dispositivos SDR"
        }
    }
    
    fun testDevice(): String {
        val count = getDeviceCount()
        if (count == 0) return "❌ No hay dispositivos"
        
        val openResult = openDevice(0)
        return if (openResult == 0) {
            closeDevice()
            "✅ Dispositivo inicializado correctamente!"
        } else {
            "❌ Error al abrir dispositivo: $openResult"
        }
    }
}
