<template>
  <div class="demo-panel">
    <p>{{ counterStore.count }}</p>
    <button class="demo-btn" @click="add">增加</button>
  </div>
</template>

<script setup lang="ts">
import { useCounterStore } from '@stores/counter.js'

const counterStore = useCounterStore()
const add = counterStore.increment
</script>
