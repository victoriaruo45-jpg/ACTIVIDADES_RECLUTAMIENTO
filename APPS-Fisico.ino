// =======================================================
// SISTEMA APPS - UNAM MOTORSPORTS
// Simulación de dos sensores APPS con protección FSAE
// =======================================================

// =======================
// CONFIGURACIÓN DE PINES
// =======================

const int apps1Pin = 34;      // Sensor APPS 1
const int apps2Pin = 35;      // Sensor APPS 2

const int pinCorto = 14;      // Entrada para detectar un cortocircuito
const int motorPin = 12;      // Salida para el motor (LED)

// =======================
// PARÁMETROS
// =======================

const int porcentajeMax = 100;
const float escalaSalida = 100.0;

const int diferenciaPermitida = 10;

const unsigned long tiempoMaxError = 100;
const unsigned long tiempoImpresion = 150;


// =======================
// VARIABLES
// =======================

unsigned long inicioError = 0;
unsigned long ultimaImpresion = 0;

bool hayError = false;
bool motorEncendido = true;

volatile bool cortoDetectado = false;


// =======================
// INTERRUPCIÓN
// =======================

void IRAM_ATTR detectarCorto() {

  cortoDetectado = true;

}



// =======================
// SETUP
// =======================

void setup() {

  Serial.begin(115200);

  pinMode(apps1Pin, INPUT);
  pinMode(apps2Pin, INPUT);

  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, HIGH);

  pinMode(pinCorto, INPUT_PULLUP);

  attachInterrupt(
    digitalPinToInterrupt(pinCorto),
    detectarCorto,
    FALLING
  );

  Serial.println();
  Serial.println("========================================");
  Serial.println(" Sistema APPS iniciado ");
  Serial.println("========================================");

}



// =======================
// LOOP PRINCIPAL
// =======================

void loop() {

  // -----------------------------
  // Revisar cortocircuito
  // -----------------------------

  if (cortoDetectado) {

    apagarMotor(
      "INTERRUPCIÓN: Cortocircuito detectado."
    );

    while (1);

  }


  // -----------------------------
  // Leer sensores
  // -----------------------------

  int lectura1 = analogRead(apps1Pin);
  int lectura2 = analogRead(apps2Pin);



  // -----------------------------
  // Convertir a porcentaje
  // -----------------------------

  int apps1Porcentaje = map(
    lectura1,
    0,
    4095,
    0,
    porcentajeMax
  );



  int apps2Porcentaje = map(
    lectura2,
    0,
    2048,
    0,
    porcentajeMax
  );



  apps1Porcentaje = constrain(
    apps1Porcentaje,
    0,
    porcentajeMax
  );



  apps2Porcentaje = constrain(
    apps2Porcentaje,
    0,
    porcentajeMax
  );



  // -----------------------------
  // Escala para telemetría
  // -----------------------------

  float apps1 =
    (apps1Porcentaje / (float)porcentajeMax)
    * escalaSalida;



  float apps2 =
    (apps2Porcentaje / (float)porcentajeMax)
    * escalaSalida;



  // -----------------------------
  // Comparar sensores
  // -----------------------------

  int discrepancia = abs(
    apps1Porcentaje - apps2Porcentaje
  );



  if (discrepancia > diferenciaPermitida) {

    if (!hayError) {

      hayError = true;
      inicioError = millis();

    }

    else {

      if (millis() - inicioError >= tiempoMaxError) {

        apagarMotor(
          "DESVIACIÓN CRÍTICA: Sensores desalineados por más de 100 ms."
        );

      }

    }

  }

  else {

    hayError = false;

  }



  // -----------------------------
  // Mostrar telemetría
  // -----------------------------

  if (millis() - ultimaImpresion >= tiempoImpresion) {

    ultimaImpresion = millis();

    mostrarDatos(
      apps1,
      apps2,
      discrepancia
    );

  }

}
// =======================
// APAGAR MOTOR
// =======================

void apagarMotor(String motivo) {

  // Evita ejecutar esta función varias veces
  if (!motorEncendido) {
    return;
  }

  motorEncendido = false;
  hayError = true;

  // Apagar motor (o LED conectado al pin 12)
  digitalWrite(motorPin, LOW);

  Serial.println();
  Serial.println("==================================================");
  Serial.println("!!! MOTOR APAGADO DE EMERGENCIA !!!");
  Serial.print("Motivo: ");
  Serial.println(motivo);
  Serial.println("==================================================");
}



// =======================
// MOSTRAR TELEMETRÍA
// =======================

void mostrarDatos(
  float apps1,
  float apps2,
  int discrepancia
) {

  Serial.print("APPS1: ");
  Serial.print(apps1, 1);

  Serial.print("% | APPS2: ");
  Serial.print(apps2, 1);

  Serial.print("% | Discrepancia: ");
  Serial.print(discrepancia);
  Serial.print("% | Estado: ");

  if (!motorEncendido) {

    Serial.println("❌ MOTOR APAGADO");

  }

  else if (hayError) {

    Serial.print("⚠️ PRE-FALLA (Tiempo acumulado: ");
    Serial.print(millis() - inicioError);
    Serial.println(" ms)");

  }

  else {

    Serial.println("✅ OK (Motor Activo)");

  }

}
