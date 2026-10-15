<template>
  <div>
    <p class="eyebrow">Async Loaded</p>
    <ul v-if="items.length">
      <li v-for="item in items" :key="item.id" class="sensor-item">
        {{ item.name }} — {{ item.value }}
      </li>
    </ul>
    <p v-else>数据加载中…</p>
  </div>
</template>

<script setup lang="ts">
import { ref, onMounted } from 'vue'

interface Sensor {
  id: number
  name: string
  value: string
}

const items = ref<Sensor[]>([])

// 模拟异步请求
async function fetchData() {
  const res = await new Promise<Sensor[]>((resolve) => {
    setTimeout(
      () =>
        resolve([
          { id: 1, name: '温度传感器', value: '24.5°C' },
          { id: 2, name: '湿度传感器', value: '62%' },
        ]),
      1200,
    )
  })
  items.value = res
}

onMounted(fetchData)
</script>

<style scoped>
.sensor-item {
  padding: var(--sp-2) 0;
  color: var(--c-muted);
}
</style>
