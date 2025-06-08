<template>
  <div>
    <Header />
    <Navega />

    <!--<router-link to="/manute" class="link-manute">Manutenção</router-link> -->

    <div class="sensores">
    <section class="sensor-container">
      <div>
        <h3>Tanque</h3>
        <p>{{ dados.tanque_TEMP }}°C</p>
        <p>{{ dados.tanque_PH }} pH</p>
      </div>

      <div v-for="n in 4" :key="n">
        <h3>Plantação {{ n }}</h3>
        <p>{{ dados[`plant_${n}_TEMP`] }}°C</p>
        <p>{{ dados[`plant_${n}_HUM`] }}%</p>
      </div>
    </section>
    </div>

    <!-- Exibição da data/hora da última leitura -->
    <p v-if="dados.time" class="data-atualizacao">Última atualização: {{ dados.time.toLocaleString() }}</p>
  </div>

  <ChartTanqueTemp
      :labels="chartLabels"
      :dataPoints="tanqueTempData"
      title="Temperatura do Tanque (Últimas Leituras)"
    />


</template>


<script>
import Header from '@/components/Header.vue';
import Navega from '@/components/Navega.vue';
import { Dados } from '@/models/sensores';
// IMPORTANTE: O nome do componente importado deve ser o que você usa no 'components' e no template.
// Se seu arquivo é 'Chart_TemTanq.vue' e ele tem 'name: 'TanqueTempChart'',
// então você deve importar com o nome que vai usar na declaração.
import ChartTanqueTemp from '@/components/charts/Chart_TemTanq.vue';

export default {
  components: {
    Header,
    Navega,
    // Use o nome do componente como ele foi definido no export do Chart_TemTanq.vue (geralmente 'name' ou inferido pelo nome do arquivo camelCase)
    // Se no Chart_TemTanq.vue você definiu `name: 'TanqueTempChart'`, use 'TanqueTempChart' aqui.
    // Se você importa como `TanqueTemp`, use `TanqueTemp` aqui e no template.
    // Eu vou assumir que no `Chart_TemTanq.vue` você definiu `name: 'TanqueTempChart'` e ajustei o import/registro aqui.
    ChartTanqueTemp // Nome usado no template: <ChartTanqueTemp>
  },

  data() {
    return {
      dados: new Dados(), // Armazena dados do Qubitro
      historicoDados: [], // <<<<< ADICIONADO: Variável para armazenar o histórico de dados para o gráfico
    };
  },

  computed: {
    chartLabels() {
      // Garante que historicoDados está disponível antes de tentar mapeá-lo
      return this.historicoDados.map(dado => new Date(dado.time).toLocaleTimeString());
    },
    tanqueTempData() {
      // Garante que historicoDados está disponível antes de tentar mapeá-lo
      return this.historicoDados.map(dado => dado.tanque_TEMP);
    }
  },

  methods: {
    async buscarDados() {
      try {
        // Altere o 'limit' para buscar mais dados para o histórico do gráfico
        // Você tinha 1000, que é muito para um gráfico e pode ser lento.
        // Recomendo um número menor para gráficos de linha, como 50 ou 100.
        const res = await fetch('/proxy-api/v2/projects/61423240-e511-4e83-a8b5-70fd8458503a/devices/92a9c650-9b11-49b5-9fdc-4c3a540bc0c9/data?page=1&limit=50&range=all', {
          headers: {
            'Authorization': 'Bearer QB_174795623003688511838ae5bd40bfba8aca23649b5e4086e6bba56f4389165ba510a31ac25d2bb567a46df3babe413284f'
          }
        });
        const json = await res.json();

        // Ordenar os dados por tempo (do mais antigo para o mais recente)
        // Isso é crucial para gráficos de linha baseados em tempo
        const dadosOrdenados = json.data.sort((a, b) => new Date(a.time) - new Date(b.time));
        this.historicoDados = dadosOrdenados; // <<<<< ATUALIZA O HISTÓRICO DE DADOS AQUI

        const ultimoDado = json.data[0]; // Qubitro geralmente retorna o mais recente primeiro
        // Atualiza a instância `dados` com os valores recebidos (para a exibição de texto)
        this.dados = Object.assign(new Dados(), {
          tanque_PH: ultimoDado.tanque_PH,
          tanque_TEMP: ultimoDado.tanque_TEMP,
          plant_1_HUM: ultimoDado.plant_1_HUM,
          plant_1_TEMP: ultimoDado.plant_1_TEMP,
          plant_2_HUM: ultimoDado.plant_2_HUM,
          plant_2_TEMP: ultimoDado.plant_2_TEMP,
          plant_3_HUM: ultimoDado.plant_3_HUM,
          plant_3_TEMP: ultimoDado.plant_3_TEMP,
          plant_4_HUM: ultimoDado.plant_4_HUM,
          plant_4_TEMP: ultimoDado.plant_4_TEMP,
          time: new Date(ultimoDado.time)
        });

      } catch (err) {
        console.error('Erro ao buscar dados do Qubitro:', err);
      }
    }
  },

  mounted() {
    this.buscarDados();
    setInterval(this.buscarDados, 10000); // Atualiza a cada 10s
  }
};
</script>

<style scoped>
.sensores{
  display: flex;
  justify-content: center; /* Centraliza horizontalmente*/
  width: 100%; /* Garante que ocupe toda a largura disponível */
  margin-top: 20px; /* espaçamento superior */
}
.sensor-container {
  display: flex;
  gap: 20px; /* espaço entre os sensores */
  flex-wrap: wrap; /* permite quebrar linha se não couber tudo */
}
.sensor-container > div {
  border: 1px solid #ccc;
  padding: 10px;
  width: 150px;
  text-align: center;
}
.link-manute {
  display: block; /* Garante que margin-top e margin-bottom funcionem */
  margin-top: 20px; /* Aumenta o espaçamento superior */
  margin-bottom: 20px; /* Aumenta o espaçamento inferior */
  text-align: center; /* Centraliza*/
}
.data-atualizacao {
  margin-top: 20px; /* Aumenta o espaçamento superior */
  margin-bottom: 20px; /* Aumenta o espaçamento inferior */
  text-align: center; /* Centraliza */
}
</style>

 