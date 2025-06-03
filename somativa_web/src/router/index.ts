import { createRouter, createWebHistory } from 'vue-router'
import Sensores from '@/views/Sensores.vue'
import Manute from '@/views/Manute.vue'


const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      component: Sensores,
      path: '/', //Pagina raiz, a primeira a aparecer
      name: 'sensores' 
    },

    {
      component: Manute,
      path: '/manute',
      name: 'manute'
    },
  ],
})

export default router
