

### **1. Visão Geral do Algoritmo Serial**
O algoritmo serial simula o movimento de partículas em um espaço 2D, onde as partículas interagem gravitacionalmente. A simulação é dividida em passos de tempo, e em cada passo, as seguintes operações são realizadas:
1. **Inicialização das partículas**.
2. **Cálculo dos centros de massa das células**.
3. **Cálculo das forças gravitacionais**.
4. **Atualização das posições e velocidades das partículas**.
5. **Verificação de colisões**.

A simulação é repetida para o número de passos de tempo especificado.

---

### **2. Detalhamento de Cada Etapa**

#### **2.1. Inicialização das Partículas**
- **Objetivo**: Gerar as partículas com posições, velocidades e massas iniciais.
- **Lógica**:
  - Use a função `init_particles()` fornecida.
  - A semente determina se as partículas são distribuídas uniformemente ou normalmente.
  - As posições (\( x \), \( y \)) são geradas dentro do espaço quadrado.
  - As velocidades (\( vx \), \( vy \)) são pequenas e aleatórias.
  - As massas (\( m \)) são proporcionais ao número de partículas e ao tamanho da grade.
- **Detalhes**:
  - Certifique-se de que as partículas estejam dentro dos limites do espaço.
  - Use `double` para armazenar posições, velocidades e massas.

---

#### **2.2. Discretização do Espaço em Células**
- **Objetivo**: Dividir o espaço em uma grade de células para simplificar o cálculo das forças.
- **Lógica**:
  - O espaço é dividido em \( ncside \times ncside \) células.
  - Cada célula tem um tamanho \( cell\_size = side / ncside \).
  - As partículas são atribuídas a células com base em suas posições.
- **Detalhes**:
  - Use a fórmula \( cell\_x = (int)(x / cell\_size) \) e \( cell\_y = (int)(y / cell\_size) \) para determinar a célula de uma partícula.
  - Certifique-se de que as células sejam indexadas corretamente (ex.: \( cell\_idx = cell\_y \times ncside + cell\_x \)).

---

#### **2.3. Cálculo dos Centros de Massa das Células**
- **Objetivo**: Calcular o centro de massa e a massa total de cada célula.
- **Lógica**:
  - Para cada célula, some as massas e as posições ponderadas das partículas.
  - O centro de massa é a média ponderada das posições:
    \[
    cm_x = \frac{\sum (x_i \cdot m_i)}{\sum m_i}, \quad cm_y = \frac{\sum (y_i \cdot m_i)}{\sum m_i}
    \]
- **Detalhes**:
  - Ignore células vazias (sem partículas).
  - Use variáveis temporárias para armazenar somas parciais.

---

#### **2.4. Cálculo das Forças Gravitacionais**
- **Objetivo**: Calcular a força gravitacional resultante em cada partícula.
- **Lógica**:
  - Para cada partícula, calcule a força resultante considerando:
    - Partículas na mesma célula.
    - Centros de massa das **oito células adjacentes**.
  - Use a fórmula da gravitação universal:
    \[
    F = G \cdot \frac{m_A \cdot m_B}{d^2}
    \]
  - A força resultante é a soma vetorial de todas as forças.
- **Detalhes**:
  - Calcule a distância \( d \) entre a partícula e o centro de massa.
  - Ignore interações se \( d^2 < \epsilon^2 \) (para evitar divisão por zero).
  - Use condições de contorno periódicas para células adjacentes (ex.: célula à esquerda da célula 0 é a última célula da linha).

---

#### **2.5. Atualização das Posições e Velocidades**
- **Objetivo**: Atualizar as posições e velocidades das partículas com base nas forças calculadas.
- **Lógica**:
  - Use a segunda lei de Newton para atualizar a velocidade:
    \[
    vx = vx + \frac{F_x}{m} \cdot \Delta t, \quad vy = vy + \frac{F_y}{m} \cdot \Delta t
    \]
  - Atualize a posição com base na velocidade:
    \[
    x = x + vx \cdot \Delta t, \quad y = y + vy \cdot \Delta t
    \]
  - Aplique condições de contorno periódicas: se uma partícula sair do espaço, ela reaparece no lado oposto.
- **Detalhes**:
  - Use \( \Delta t = 0.1 \) para o intervalo de tempo.
  - Certifique-se de que as posições estejam dentro dos limites do espaço.

---

#### **2.6. Verificação de Colisões**
- **Objetivo**: Verificar se duas partículas colidiram e removê-las da simulação.
- **Lógica**:
  - Para cada par de partículas, calcule a distância \( d \).
  - Se \( d^2 < \epsilon^2 \), marque as partículas como colididas.
  - Partículas colididas são removidas (ex.: massa = 0).
- **Detalhes**:
  - Evite comparar partículas já colididas.
  - Conte o número de colisões para a saída.

---

### **3. Fluxo do Algoritmo Serial**
1. **Inicialização**:
   - Leia os parâmetros de entrada.
   - Inicialize as partículas com `init_particles()`.
2. **Loop de Passos de Tempo**:
   - Para cada passo de tempo:
     - Calcule os centros de massa das células.
     - Calcule as forças gravitacionais.
     - Atualize as posições e velocidades.
     - Verifique colisões.
3. **Saída**:
   - Imprima a posição final da partícula 0.
   - Imprima o número de colisões.

---

### **4. Considerações Finais**
- **Precisão Numérica**: Use `double` para evitar erros de arredondamento.
- **Eficiência**: Evite cálculos redundantes e otimize os loops.
- **Validação**: Compare os resultados com os exemplos fornecidos.