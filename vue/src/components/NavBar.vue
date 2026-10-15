<template>
  <header class="nav-bar">
    <div class="nav-inner">
      <RouterLink to="/" class="brand">
        <span class="brand-dot" aria-hidden="true"></span>
        Vue Indoor
      </RouterLink>
      <nav class="nav-links">
        <RouterLink to="/" class="nav-link">首页</RouterLink>
        <RouterLink to="/about" class="nav-link">关于</RouterLink>
        <RouterLink to="/data" class="nav-link">数据</RouterLink>
        <RouterLink to="/play" class="nav-link">操场</RouterLink>
      </nav>
    </div>
  </header>
</template>

<script setup lang="ts">
import { RouterLink } from 'vue-router'
</script>

<style scoped>
.nav-bar {
  width: 100%;
  background: var(--c-surface);
  border-bottom: 1px solid var(--c-line);
}

.nav-inner {
  margin: 0 auto;
  height: 56px;
  padding: 0 var(--sp-6);
  display: flex;
  align-items: center;
  justify-content: space-between;
}

.brand {
  display: inline-flex;
  align-items: center;
  gap: var(--sp-2);
  font-family: var(--ff-display);
  font-size: 1.125rem;
  font-weight: 600;
  letter-spacing: -0.01em;
  color: var(--c-ink);
  text-decoration: none;
}

.brand-dot {
  width: 10px;
  height: 10px;
  border-radius: 50%;
  background: var(--c-teal);
  box-shadow: 0 0 0 4px var(--c-mint);
}

.nav-links {
  display: flex;
  align-items: center;
  gap: var(--sp-6);
}

.nav-link {
  font-size: var(--fs-base);
  color: var(--c-muted);
  padding: 6px 2px;
  border-bottom: 2px solid transparent;
  transition:
    color 0.2s ease,
    border-color 0.2s ease;
}

.nav-link:hover {
  color: var(--c-teal-strong);
}

.nav-link.router-link-exact-active {
  color: var(--c-teal);
  border-bottom-color: var(--c-teal);
}
</style>
