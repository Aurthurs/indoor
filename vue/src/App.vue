<template>
  <NavBar />
  <main class="page">
    <RouterView />
  </main>
</template>

<script setup lang="ts">
import NavBar from '@components/NavBar.vue'
</script>

<style scoped>
.page {
  max-width: 72rem;
  margin: 0 auto;
  padding: var(--sp-8) var(--sp-6) var(--sp-12);
}
</style>
