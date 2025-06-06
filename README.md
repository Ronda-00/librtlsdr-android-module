# Módulo de Librería RTL-SDR para Android (Compilable)

Este repositorio contiene un módulo de librería de Android para `librtlsdr`, listo para ser incluido y compilado en proyectos modernos.

## El Problema que Resuelve

Las librerías existentes para RTL-SDR en Android, como la original de `keesj/librtlsdr-android`, a menudo no compilan con las versiones actuales del NDK de Android. Este módulo contiene todo el código fuente con las correcciones necesarias para que compile exitosamente.

## Cómo Usar

1.  En el archivo **`settings.gradle`** de tu proyecto, añade este repositorio usando JitPack y el nombre del módulo:
    ```gradle
    // settings.gradle
    dependencyResolutionManagement {
        repositories {
            google()
            mavenCentral()
            maven { url 'https://jitpack.io' } // <-- Añadir JitPack
        }
    }
    include ':app'
    ```

2.  En el archivo **`build.gradle` del módulo de tu aplicación** (normalmente `app/build.gradle`), añade la dependencia apuntando a este repositorio de GitHub:
    ```gradle
    // app/build.gradle
    dependencies {
        // Reemplaza 'tu-usuario' con tu nombre de usuario de GitHub
        implementation 'com.github.tu-usuario:librtlsdr-android-module:main-SNAPSHOT'
        
        // ... tus otras dependencias
    }
    ```

3.  Sincroniza tu proyecto en Android Studio. ¡Ya está listo!

## Créditos

Este trabajo se basa en el código y la estructura del repositorio [keesj/librtlsdr-android](https://github.com/keesj/librtlsdr-android).
