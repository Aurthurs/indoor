<template>
  <div>
    <p class="eyebrow">Components</p>
    <h1>组件通信</h1>
    <p class="lead">Props / Emit / v-model / Pinia / Slot 五种通信方式示例。</p>

    <div class="demo-grid">
      <section class="demo-card">
        <h2>Props</h2>
        <p class="demo-desc">父传子，子组件只读展示</p>
        <div class="demo-body">
          <TopOne :msg="msg1" />
        </div>
      </section>

      <section class="demo-card">
        <h2>Emit</h2>
        <p class="demo-desc">子传父，通过事件回调</p>
        <div class="demo-body">
          <TopTwo @send-message="handleMessage" />
        </div>
        <p class="demo-result">子组件消息：{{ receivedMessage || '（未收到）' }}</p>
      </section>

      <section class="demo-card">
        <h2>v-model</h2>
        <p class="demo-desc">双向绑定</p>
        <div class="demo-body">
          <TopThree v-model:count="count" />
        </div>
        <p class="demo-result">父组件 count：{{ count }}</p>
      </section>

      <section class="demo-card">
        <h2>Pinia</h2>
        <p class="demo-desc">跨组件全局状态</p>
        <div class="demo-body">
          <TopFour />
        </div>
        <p class="demo-result">全局存储 count：{{ counterStore.count }}</p>
      </section>

      <section class="demo-card demo-card--wide">
        <h2>Slot</h2>
        <p class="demo-desc">插槽分发内容</p>
        <div class="demo-body">
          <SlotOne :items="users">
            <template #front-slot>
              <p class="slot-demo">父组件传入的插槽内容</p>
            </template>
            <template #item="{ todo }">
              <p class="slot-demo">{{ todo.name }}</p>
            </template>
          </SlotOne>
        </div>
      </section>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'
import TopOne from '@components/TopOne.vue'
import TopTwo from '@/components/TopTwo.vue'
import TopThree from '@/components/TopThree.vue'
import TopFour from '@/components/TopFour.vue'
import SlotOne from '@/components/SlotOne.vue'
import { useCounterStore } from '@stores/counter.js'

const msg1 = 'Hello from HomeView'
const receivedMessage = ref('')
const count = ref(0)
const counterStore = useCounterStore()

const users = ref([
  { id: 1, name: '张三' },
  { id: 2, name: '李四' },
])

// 处理子组件传递来的数据
const handleMessage = (msg: string) => {
  receivedMessage.value = msg
}
</script>

<style scoped>
.lead {
  color: var(--c-muted);
  margin-bottom: var(--sp-8);
}

.demo-grid {
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  gap: var(--sp-6);
}

.demo-card {
  background: var(--c-surface);
  border: 1px solid var(--c-line);
  border-radius: var(--r-lg);
  padding: var(--sp-6);
  box-shadow: var(--sh-sm);
}

.demo-card--wide {
  grid-column: 1 / -1;
}

.demo-card h2 {
  font-size: var(--fs-lg);
  margin-bottom: var(--sp-2);
}

.demo-desc {
  color: var(--c-faint);
  font-size: var(--fs-sm);
  margin-bottom: var(--sp-5);
}

.demo-body {
  margin-bottom: var(--sp-4);
}

.demo-result {
  font-size: var(--fs-sm);
  color: var(--c-teal-strong);
  background: var(--c-mint);
  border-radius: var(--r-sm);
  padding: var(--sp-2) var(--sp-3);
}

.slot-demo {
  margin-bottom: var(--sp-2);
}

@media (max-width: 48rem) {
  .demo-grid {
    grid-template-columns: 1fr;
  }
}
</style>
