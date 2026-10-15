<template>
  <div class="demo-panel slot-demo">
    <section class="slot-section">
      <p class="slot-label">具名插槽 · front-slot</p>
      <p class="slot-desc">父组件通过 <code>#front-slot</code> 传入的静态内容</p>
      <div class="slot-body">
        <slot name="front-slot">front-slot 默认内容</slot>
      </div>
    </section>

    <section class="slot-section">
      <p class="slot-label">作用域插槽 · item</p>
      <p class="slot-desc">父组件通过 <code>#item="{ todo }"</code> 接收子组件数据渲染</p>
      <ul>
        <li v-for="item in items" :key="item.id">
          <slot name="item" :todo="item"></slot>
        </li>
      </ul>
    </section>
  </div>
</template>

<script setup lang="ts">
interface Item {
  id: number
  name: string
}

defineProps<{
  items: Item[]
}>()
</script>

<style scoped>
.slot-section + .slot-section {
  margin-top: var(--sp-5);
  padding-top: var(--sp-5);
  border-top: 1px dashed var(--c-line-strong);
}

.slot-label {
  font-weight: 600;
  color: var(--c-teal-strong);
}

.slot-desc {
  font-size: var(--fs-sm);
  color: var(--c-faint);
  margin-bottom: var(--sp-3);
}

.slot-body {
  background: var(--c-surface);
  border: 1px solid var(--c-line);
  border-radius: var(--r-sm);
  padding: var(--sp-3) var(--sp-4);
}
</style>
