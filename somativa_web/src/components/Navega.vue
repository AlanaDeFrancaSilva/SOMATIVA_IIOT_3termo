<template>
    <div class="navega">

        <nav class="navegacao">
      <ul>
        <li>
          <router-link to="/">Home</router-link>
        </li>
        <li>
          <span class="separator">/</span>
          <router-link to="/manute">Manutenção</router-link>
        </li>
      </ul>
    </nav>

    </div>
</template>

<style lang="scss" scoped>
.navegacao {
  padding: 10px 20px; /* Adicione um pouco de padding para espaçamento */
  
  font-family: Arial, sans-serif; /* Fonte simples */
  font-size: 0.9em;
}

.navegacao ul {
  list-style: none; /* Remove os marcadores de lista */
  padding: 0;
  margin: 0;
  display: flex; /* Para alinhar os itens em uma linha */
  align-items: center; /* Alinha verticalmente */
}

.navegacao li {
  display: flex; /* Garante que o item e o separador fiquem lado a lado */
  align-items: center;
}

.navegacao a {
  text-decoration: none; /* Remove sublinhado dos links */
  color: #000000; /* Cor links */
  transition: color 0.2s ease-in-out; /* Transição suave na cor */
}

.navegacao a:hover {
  color: #0056b3; /* Cor mais escura ao passar o mouse */
  text-decoration: underline; /* Adiciona sublinhado ao passar o mouse */
}

.navegacao .separator {
  margin: 0 8px; /* Espaço ao redor do separador */
  color: #888; /* Cor cinza para o separador */
}
</style>