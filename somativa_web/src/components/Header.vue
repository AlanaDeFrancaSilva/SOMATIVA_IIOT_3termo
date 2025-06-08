<template>
  <div class="header">
    <div class="grupo-esquerda">
    <img class="menu" src="@/assets/image/menu.png" alt="menu">
    <img class="logo" src="@/assets/image/logo.png" alt="Logo" />
    </div>

    <div class="grupo-direita">
      <img src="@/assets/image/notification.png" alt="notificacao" />
      <img src="@/assets/image/user.png" alt="user" @click="togglePanel"/>
    </div>
  </div>

   <!-- Painel lateral -->
  <div class="side-panel" :class="{ open: showPanel }">
    <div class="side-header">
      <p>Bem-vindo!</p>
      <button @click="togglePanel">Fechar</button>
    </div>
    <div class="side-content">
      <!-- Conteúdo do painel lateral -->
      <p>Perfil do usuário, configurações, etc.</p>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'

const showPanel = ref(false)

const togglePanel = () => {
  showPanel.value = !showPanel.value
}
</script>

<style lang="scss" scoped>
.header {
  background-color: #1A5943; // Cor de fundo 
  display: flex; // Alinha os elementos horizontalmente
  align-items: center; // Centraliza verticalmente
  justify-content: space-between; // Espaça os elementos nas extremidades
  padding: 1rem 2rem; // Espaçamento interno (superior/inferior e laterais)
  color: white; // Cor do texto padrão

.grupo-esquerda {
  display: flex;
  align-items: center;
  gap: 1rem; // Espaço entre menu e logo
}

.title {
  font-size: 1.8rem; // Tamanho da fonte do título
  font-weight: bold; // Negrito
  color: white; // Cor do texto
  margin: 0; // Remove margem padrão
}

.logo {
  height: 50px; // Altura da imagem da logo
}

.menu {
  height: 25px; 
  cursor: pointer; // tornar clicável
}

.grupo-direita {
  display: flex; // Alinha os ícones horizontalmente
  gap: 2rem; // Espaço entre os ícones

  img {
    height: 32px; // Tamanho dos ícones (notificação e usuário)
    cursor: pointer; // Muda o cursor ao passar por cima
    }
  }
}

/* Painel lateral */
.side-panel {
  position: fixed;
  top: 0;
  right: -300px;
  width: 300px;
  height: 100vh;
  background-color: #f5f5f5;
  box-shadow: -2px 0 6px rgba(0, 0, 0, 0.2);
  padding: 1rem;
  transition: right 0.3s ease;
  z-index: 1000;

  &.open {
    right: 0;
  }

  .side-header {
    display: flex;
    justify-content: space-between;
    align-items: center;

    button {
      background: none;
      border: none;
      font-size: 1rem;
      cursor: pointer;
    }
  }

  .side-content {
    margin-top: 1rem;
  }
}
</style>
