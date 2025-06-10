<template>
  <div>
    <Header />
    <Navega />
    <h1>Registrar Manutenção</h1>

    <form @submit.prevent="salvarManutencao" class="manutencao-form">
      
<div class="form-group">
        <label for="codigoManutencao">Código da Manutenção:</label>
        <input
          type="text"
          v-model="codigoManutencao"
          id="codigoManutencao"
          placeholder="Ex: 0001, 0002"
          class="form-input"
        />
      </div>

      <div class="form-group">
        <label for="equipamento">Equipamento:</label>
        <select v-model="equipamentoSelecionado" id="equipamento" required class="form-input">
          <option disabled value="">Selecione um equipamento</option>
          <option v-for="eq in equipamentos" :key="eq.id" :value="eq.id">
            {{ eq.nome }}
          </option>
        </select>
      </div>

      <div class="form-group">
        <label for="data">Data:</label>
        <input type="date" v-model="dataManutencao" id="data" required class="form-input" />
      </div>

      <div class="form-group">
        <label for="descricao">Descrição:</label>
        <textarea
          v-model="descricao"
          id="descricao"
          rows="4"
          placeholder="Descreva o que foi feito na manutenção"
          required
          class="form-input"
        ></textarea>
      </div>

      <button type="submit" class="submit-button">Salvar Manutenção</button>
    </form>
  </div>
</template>

<script setup>
import Header from '@/components/Header.vue';
import Navega from '@/components/Navega.vue';
import { ref, onMounted } from 'vue';
import { getEquipamentos } from '@/services/services.config.ts';
import { criarManutencao } from '@/services/apiService.ts';

// Lista de equipamentos disponíveis
const equipamentos = ref([]);

// Dados do formulário
const equipamentoSelecionado = ref('');
const dataManutencao = ref('');
const descricao = ref('');
const codigoManutencao = ref(''); // Novo ref para o código

// Carregar equipamentos ao montar o componente
onMounted(async () => {
  try {
    const response = await getEquipamentos();
    console.log('Resposta do Contentful:', response);
    equipamentos.value = response.items.map(item => ({
      id: item.sys.id,
      ...item.fields
    }));
    console.log('Equipamentos Processados:', equipamentos.value);
  } catch (error) {
    console.error('Erro ao buscar equipamentos:', error);
  }
});

// Função que será chamada ao submeter o formulário
async function salvarManutencao() {
  await criarManutencao({
    equipamentoId: equipamentoSelecionado.value,
    data: dataManutencao.value,
    descricao: descricao.value,
    codigoManutencao: codigoManutencao.value // Inclua o código na chamada
  });

  alert('Manutenção registrada com sucesso!');
  equipamentoSelecionado.value = '';
  dataManutencao.value = '';
  descricao.value = '';
  codigoManutencao.value = ''; // Limpe o campo do código após o envio
}
</script>

<style scoped>
/* Estilos para o contêiner principal do formulário */
.manutencao-form {
  max-width: 600px; /* Largura máxima para o formulário */
  margin: 40px auto; /* Margem superior/inferior de 40px, auto centraliza */
  padding: 30px; /* Preenchimento interno */
  background-color: #f9f9f9; /* Cor de fundo suave */
  border: 1px solid #ddd; /* Borda sutil */
  border-radius: 12px; /* Bordas arredondadas */
  box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); /* Sombra suave */
}

/* Espaçamento entre os grupos de formulário (label + input) */
.form-group {
  margin-bottom: 20px; /* Espaço abaixo de cada grupo de campo */
}

/* Estilo para as labels (nome do campo acima do input) */
.form-group label {
  display: block; /* Garante que a label fique em sua própria linha */
  margin-bottom: 8px; /* Espaço entre a label e o input */
  font-weight: bold; /* Deixa o texto da label em negrito */
  color: #333; /* Cor do texto da label */
}

/* Estilo para todos os inputs e selects */
.form-input {
  width: 100%; /* Ocupa 100% da largura disponível no contêiner */
  padding: 12px; /* Preenchimento interno */
  border: 1px solid #ccc; /* Borda padrão */
  border-radius: 8px; /* Bordas levemente arredondadas para os inputs */
  box-sizing: border-box; /* Garante que o padding não aumente a largura total */
  font-size: 1rem; /* Tamanho da fonte */
  line-height: 1.5; /* Altura da linha para melhor legibilidade */
}

/* Estilo específico para o textarea */
textarea.form-input {
  resize: vertical; /* Permite redimensionar apenas verticalmente */
  min-height: 100px; /* Altura mínima para o textarea */
}

/* Estilo para o botão de submit */
.submit-button {
  display: block; /* Ocupa sua própria linha */
  width: 100%; /* Ocupa 100% da largura do formulário */
  padding: 15px; /* Preenchimento interno */
  background-color: #4CAF50; /* Cor de fundo verde */
  color: white; /* Texto branco */
  border: none; /* Sem borda */
  border-radius: 8px; /* Bordas arredondadas */
  font-size: 1.1rem; /* Tamanho da fonte maior */
  font-weight: bold; /* Texto em negrito */
  cursor: pointer; /* Cursor de mão ao passar por cima */
  transition: background-color 0.3s ease; /* Transição suave para o hover */
}

.submit-button:hover {
  background-color: #45a049; /* Escurece um pouco no hover */
}

/* Estilos existentes para as opções do select (mantidos) */
select option[disabled] {
  color: #999;
}

select option:first-child[disabled] {
  color: #777;
}
</style>