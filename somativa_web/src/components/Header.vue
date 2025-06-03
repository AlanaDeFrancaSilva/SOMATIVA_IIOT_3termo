<template>
  <div class="header">
    <img class="logo" src="@/assets/image/logo.png" alt="Logo" />

    <div class="header-icons">
      <img src="@/assets/image/notification.png" alt="notificacao" />
      <img src="@/assets/image/user.png" alt="user" />
    </div>
  </div>
</template>

<style lang="scss" scoped>
.header {
  background-color: #1A5943; // Cor de fundo 
  display: flex; // Alinha os elementos horizontalmente
  align-items: center; // Centraliza verticalmente
  justify-content: space-between; // Espaça os elementos nas extremidades
  padding: 1rem 2rem; // Espaçamento interno (superior/inferior e laterais)
  color: white; // Cor do texto padrão

  .title {
    font-size: 1.8rem; // Tamanho da fonte do título
    font-weight: bold; // Negrito
    color: white; // Cor do texto
    margin: 0; // Remove margem padrão
  }

  .logo {
    height: 50px; // Altura da imagem da logo
  }

  .header-icons {
    display: flex; // Alinha os ícones horizontalmente
    gap: 2rem; // Espaço entre os ícones

    img {
      height: 32px; // Tamanho dos ícones (notificação e usuário)
      cursor: pointer; // Muda o cursor ao passar por cima
    }
  }
}
</style>
