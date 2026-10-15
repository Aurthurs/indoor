import { createRouter, createWebHistory } from 'vue-router'
import HomeView from '@views/HomeView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'home',
      component: HomeView,
    },
    {
      path: '/about',
      name: 'about',
      component: () => import('@views/AboutView.vue'),
    },
    {
      path: '/data',
      name: 'data',
      component: () => import('@views/DataView.vue'),
    },
    {
      path: '/play',
      name: 'play',
      component: () => import('@views/PlayGround.vue'),
    },
  ],
})

export default router
