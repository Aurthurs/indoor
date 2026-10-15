<template>
  <div>
    <p class="eyebrow">Data</p>
    <h1>数据</h1>
    <p>异步懒加载示例：组件按需加载，挂载后异步获取数据。</p>
    <Suspense>
      <AsyncData />
    </Suspense>
  </div>
</template>

<script setup lang="ts">
import { defineAsyncComponent, defineComponent, h } from 'vue'

// 异步懒加载子组件：用到才加载，加载期间显示 Loading
const AsyncData = defineAsyncComponent({
  loader: () => import('@components/AsyncData.vue'),
  delay: 200,
})
</script>
