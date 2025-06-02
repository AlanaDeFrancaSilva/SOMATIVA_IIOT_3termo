import { createRouter, createWebHistory } from 'vue-router'
import Sensores from '@/views/Sensores.vue'


const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      component: Sensores,
      path: '/', //Pagina raiz, a primeira a aparecer
      name: 'sensores' 
    },
  ],
})

export default router
