# ACTIVIDADES_RECLUTAMIENTO
Sistema de plausibilidad APPS y análisis de telemetría
## Cronograma de Desarrollo y Bitácora de Trabajo

El proyecto se estructuró y completó en un periodo de **4 días de desarrollo activo** (del 13 de Julio al 17 de Julio), distribuyendo las tareas de hardware, software, análisis de datos y visualización para asegurar el cumplimiento de todos los entregables solicitados:

| Día | Actividad Realizada | Entregables y Requerimientos Cubiertos |
| :--- | :--- | :--- |
| **Día 1** | **Análisis de Requisitos e Integridad de Datos**<br>• Carga y auditoría del dataset de telemetría sin procesar (`data.csv`).<br>• Detección inicial de fallas de integridad en el sensor inercial (detección del corte de señal de 1.5 s). | • `Ruíz Ortiz Aylin Victoria - data.csv`<br>• Validación de frecuencia de muestreo a 100 Hz. |
| **Día 2** | **Procesamiento de Señal y Análisis de Telemetría**<br>• Implementación del pipeline en Python con filtro pasa-bajas Butterworth de fase cero (`filtfilt`).<br>• Generación del diagrama G-G y cálculo de la magnitud de la fuerza G combinada limpia (1.26 G). | • `Ruíz Ortiz Aylin Victoria - Análisis de Telemetría.ipynb`<br>• Eliminación del ruido estructural de alta frecuencia en el dataset. |
| **Día 3** | **Diseño del Circuito APPS y Firmware Embebido**<br>• Modelado de la simulación del circuito APPS físico con doble potenciómetro asimétrico a 5V.<br>• Programación del algoritmo de plausibilidad física, lógica de interrupción por cortocircuito y regla de persistencia de 100 ms. | • `APPS-Fisico.ino`<br>• Simulación y cableado del circuito físico en protoboard. |
| **Día 4** | **Dashboard Web, Documentación y Cierre**<br>• Desarrollo del dashboard interactivo de visualización temporal en tiempo real con indicador de peligro.<br>• Diagnóstico técnico de la asimetría del diagrama G-G, redacción del reporte formal en LaTeX e integración bajo *Conventional Commits*. | • `dashboard_telemetria.html`<br>• `Reporte_Técnico.pdf`<br>• `README.md` completo. |

---

## Estructura del Repositorio y Entregables

*   📁 **`APPS-Fisico.ino`**: Código de control para el microcontrolador. Traduce los rangos asimétricos de los sensores de los pedales a una escala común, gestiona las interrupciones por cortocircuito y aplica la regla de persistencia de 100 ms ante ruido o falsos contactos.
*   📁 **`Ruíz Ortiz Aylin Victoria - Análisis de Telemetría.ipynb`**: Notebook de Python con el pipeline reproducible de acondicionamiento de señal (filtro Butterworth) y detección automatizada de anomalías.
*   📁 **`dashboard_telemetria.html`**: Dashboard web interactivo que grafica las variables dinámicas en el tiempo y cuenta con un indicador visual crítico de peligro para las violaciones de plausibilidad.
*   📁 **`Reporte_Técnico.pdf`**: Reporte técnico breve que sintetiza el diagnóstico mecánico/eléctrico y define las acciones recomendadas para el chasis y la electrónica.
