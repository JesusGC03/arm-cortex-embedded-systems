#include <LPC17xx.H>

//-------------------------------------------------------------
// CONFIGURACIÓN DE PINES
//-------------------------------------------------------------
void inicioPINSEL(void) {
    // --- P2.10 (EINT0) y P2.11 (EINT1) ---
    LPC_PINCON->PINSEL4 &= ~(0xF << 20);       // Limpia bits 20–23
    LPC_PINCON->PINSEL4 |=  (1 << 20) | (1 << 22);  // P2.10->EINT0, P2.11->EINT1
    // Resultado esperado: PINSEL4 = 0x00150000

    // --- Activar resistencias de pull-up internas ---
    LPC_PINCON->PINMODE4 &= ~((3 << 20) | (3 << 22));  // 00 = pull-up enabled

    // --- LEDs en P0.4 y P0.6 ---
    LPC_PINCON->PINSEL0 &= ~((3 << 8) | (3 << 12)); // GPIO puro
    LPC_GPIO0->FIODIR |= (1 << 4) | (1 << 6);       // P0.4 y P0.6 como salida
    LPC_GPIO0->FIOCLR = (1 << 4) | (1 << 6);        // LEDs apagados al inicio
}

//-------------------------------------------------------------
// CONFIGURACIÓN DE INTERRUPCIONES
//-------------------------------------------------------------
void inicioIRQs(void) {
    // --- Configuración de flancos ---
    LPC_SC->EXTMODE  = 0x03;   // EINT0 y EINT1 activadas por flanco
    LPC_SC->EXTPOLAR = 0x00;   // 0 = flanco descendente (pulsación)
    
    // --- Limpiar banderas antes de habilitar ---
    LPC_SC->EXTINT = 0x03;               // limpia flags EINT0 y EINT1
    NVIC_ClearPendingIRQ(EINT0_IRQn);
    NVIC_ClearPendingIRQ(EINT1_IRQn);

    // --- Misma prioridad → sin desalojo ---
    NVIC_SetPriorityGrouping(4);
    NVIC_SetPriority(EINT0_IRQn, 5);
    NVIC_SetPriority(EINT1_IRQn, 5);

    // --- Habilitar interrupciones ---
    NVIC_EnableIRQ(EINT0_IRQn);
    NVIC_EnableIRQ(EINT1_IRQn);
}

//-------------------------------------------------------------
// RUTINAS DE ATENCIÓN A INTERRUPCIONES (ISR)
//-------------------------------------------------------------
void EINT0_IRQHandler(void) {
    LPC_SC->EXTINT = (1 << 0);       // Borra bandera EINT0
    LPC_GPIO0->FIOSET = (1 << 4);    // Enciende LED P0.4
    LPC_GPIO0->FIOCLR = (1 << 6);    // Apaga LED P0.6
}

void EINT1_IRQHandler(void) {
    LPC_SC->EXTINT = (1 << 1);       // Borra bandera EINT1
    LPC_GPIO0->FIOSET = (1 << 6);    // Enciende LED P0.6
    LPC_GPIO0->FIOCLR = (1 << 4);    // Apaga LED P0.4
}

//-------------------------------------------------------------
// PROGRAMA PRINCIPAL
//-------------------------------------------------------------
int main(void) {
    inicioPINSEL();
    inicioIRQs();

    while (1);  // bucle infinito
}
