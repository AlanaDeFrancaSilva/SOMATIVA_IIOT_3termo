<template>
  <div class="chart-wrapper">
    <h3>{{ title }}</h3>
    <LineChart :data="chartData" :options="chartOptions" />
  </div>
</template>

<script>
// Importa o componente de gráfico de linha específico do 'vue-chartjs'.
// 'Line' é um wrapper para o Chart.js que facilita o uso em componentes Vue.
import { Line } from 'vue-chartjs';
// Importa os elementos essenciais do Chart.js que precisam ser registrados.
// Sem eles, o Chart.js não sabe como desenhar linhas, títulos, etc.
import {
  Chart as ChartJS,      // A classe principal do Chart.js
  Title,                  // Para exibir o título do gráfico
  Tooltip,                // Para exibir informações ao passar o mouse sobre os pontos
  Legend,                 // Para exibir a legenda das séries de dados
  LineElement,            // Para desenhar as linhas do gráfico
  CategoryScale,          // Para escalas categóricas (como rótulos de tempo no eixo X)
  LinearScale,            // Para escalas lineares (como valores de temperatura no eixo Y)
  PointElement            // Para desenhar os pontos de dados no gráfico
} from 'chart.js';

// Registra os componentes importados do Chart.js.
// Isso os torna disponíveis para serem usados pelo LineChart.
ChartJS.register(Title, Tooltip, Legend, LineElement, CategoryScale, LinearScale, PointElement);

// Exporta a definição do componente Vue.
export default {
  // Define o nome do componente. Útil para depuração em ferramentas de desenvolvedor do Vue.
  name: 'TanqueTempChart',
  // Declara quais outros componentes este componente vai usar.
  // Aqui, Line (importado como LineChart) é usado no template.
  components: {
    LineChart: Line // Renomeia 'Line' para 'LineChart' para maior clareza no template.
  },
  // 'props' são propriedades personalizadas que este componente pode receber de seu componente pai.
  // Elas permitem que o componente seja reutilizável com diferentes dados.
  props: {
    // 'labels' será um array de rótulos para o eixo X (geralmente tempo).
    labels: {
      type: Array,    // Especifica que o tipo esperado é Array.
      required: true  // Indica que esta prop é obrigatória; o componente não funcionará sem ela.
    },
    // 'dataPoints' será um array de valores para o eixo Y (geralmente temperatura).
    dataPoints: {
      type: Array,    // Especifica que o tipo esperado é Array.
      required: true  // Indica que esta prop é obrigatória.
    },
    // 'title' será o texto do título do gráfico.
    title: {
      type: String,   // Especifica que o tipo esperado é String.
      default: 'Gráfico' // Define um valor padrão caso a prop não seja fornecida.
    }
  },
  // 'data' é uma função que retorna o estado reativo local do componente.
  // Neste caso, ele contém as opções de configuração do gráfico.
  data() {
    return {
      // Objeto de opções do Chart.js para configurar o gráfico.
      chartOptions: {
        responsive: true,           // Faz o gráfico se ajustar ao tamanho do seu container.
        maintainAspectRatio: false, // Permite que você defina a altura/largura livremente sem manter a proporção.
        // Adiciona padding ao layout do gráfico para "empurrar" o conteúdo para dentro
        layout: {
          padding: {
            bottom: 30 // Adiciona padding na parte inferior do layout do gráfico
          }
        },
        scales: {                   // Configurações dos eixos do gráfico.
          x: {                      // Configurações para o eixo X.
            title: {
              display: true,        // Exibe o título do eixo.
              text: 'Hora da Leitura' // Texto do título do eixo X.
            }
          },
          y: {                      // Configurações para o eixo Y.
            title: {
              display: true,        // Exibe o título do eixo.
              text: 'Temperatura (°C)' // Texto do título do eixo Y.
            }
          }
        }
      }
    };
  },
  // 'computed' properties são propriedades que dependem de outras propriedades reativas
  // (dados, props, outras computadas). Elas são cacheadas e só são recalculadas quando
  // suas dependências mudam.
  computed: {
    // 'chartData' é uma computed property que formata as 'props' (labels e dataPoints)
    // no formato específico que o Chart.js espera para seus dados.
    chartData() {
      return {
        labels: this.labels, // Define os rótulos do eixo X com base na prop 'labels'.
        datasets: [          // Um array de conjuntos de dados (cada um representa uma linha/barra/etc.).
          {
            label: 'Temperatura do Tanque (°C)', // Legenda para esta série de dados.
            backgroundColor: '#1A5943',         // Cor de fundo (útil para gráficos de área ou barras).
            borderColor: '#1A5943',             // Cor da linha do gráfico.
            data: this.dataPoints,              // Os valores numéricos para esta série de dados.
            tension: 0.4                        // Adiciona uma pequena curva à linha do gráfico (0 para linha reta).
          }
        ]
      };
    }
  }
};
</script>

<style scoped>
/* A tag 'scoped' limita estes estilos apenas a este componente,
   evitando que eles afetem outros componentes na aplicação. */

/* Estilos para o container principal do gráfico. */
.chart-wrapper {
  margin-top: 40px;      /* Espaçamento superior externo. */
  padding: 20px;         /* Espaçamento interno. */
  border: 1px solid #eee; /* Borda leve. */
  border-radius: 8px;    /* Cantos arredondados. */
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1); /* Sombra suave para um efeito 3D. */
  max-width: 600px;      /* largura máxima para o gráfico, evitando que ele fique muito largo. */
  max-height: 400px; /* altura máxima para o gráfico */
  margin-left: auto;     /* Centraliza o container horizontalmente. */
  margin-right: auto;    /* Complementa o margin-left: auto para centralização. */
}

/* Estilos para o título dentro do container do gráfico. */
.chart-wrapper h3 {
  text-align: center;    /* Centraliza o texto do título. */
  margin-bottom: 20px;   /* Espaçamento abaixo do título. */
}
</style>