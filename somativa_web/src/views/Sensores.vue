<template>
  <div>
    <Header />

    <router-link to="/manute">Manutenção</router-link>

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

    <!-- Exibição da data/hora da última leitura -->
    <p v-if="dados.time">Última atualização: {{ dados.time.toLocaleString() }}</p>
  </div>
</template>


<script>
import Header from '@/components/Header.vue';
import { Dados } from '@/models/sensores'; // ajuste o caminho conforme a estrutura do seu projeto

export default {
  components: {
    Header
  },

  data() {
    return {
      dados: new Dados()
    };
  },

  methods: {
    async buscarDados() {
      try {
        const res = await fetch('/proxy-api/v2/projects/61423240-e511-4e83-a8b5-70fd8458503a/devices/92a9c650-9b11-49b5-9fdc-4c3a540bc0c9/data?page=1&limit=1000&range=all', {
          headers: {
            'Authorization': 'Bearer QB_174795623003688511838ae5bd40bfba8aca23649b5e4086e6bba56f4389165ba510a31ac25d2bb567a46df3babe413284f'
          }
        });
        const json = await res.json();

        const ultimoDado = json.data[0];

        // Atualiza a instância `dados` com os valores recebidos
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
.sensor-container {
  display: flex;
  gap: 20px; /* espaço entre os sensores */
  flex-wrap: wrap; /* permite quebrar linha se não couber tudo */
}
.sensor-container > div {
  border: 1px solid #ccc;
  padding: 10px;
  width: 150px; /* ajuste conforme necessário */
  text-align: center;
}
</style>

 