<template>
  <div>
    <p class="eyebrow">Dynamic</p>
    <h1>动态组件</h1>
    <p class="lead">通过 <code>&lt;component :is&gt;</code> 在多个组件间切换。</p>

    <div class="card">
      <div class="tabs" role="tablist">
        <button
          v-for="tab in tabList"
          :key="tab.key"
          type="button"
          role="tab"
          class="tab"
          :class="{ 'tab--active': currentTab === tab.key }"
          @click="currentTab = tab.key"
        >
          {{ tab.label }}
        </button>
      </div>

      <div class="tab-panel">
        <component :is="tabs[currentTab]" />
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import TopOne from '@components/TopOne.vue'
import TopThree from '@components/TopThree.vue'
import { ref } from 'vue'

const tabList = [
  { key: 'topOne', label: 'TopOne' },
  { key: 'topThree', label: 'TopThree' },
] as const

const currentTab = ref<'topOne' | 'topThree'>('topOne')
const tabs = { topOne: TopOne, topThree: TopThree }
</script>

<style scoped>
.lead {
  color: var(--c-muted);
  margin-bottom: var(--sp-8);
}

.card {
  background: var(--c-surface);
  border: 1px solid var(--c-line);
  border-radius: var(--r-lg);
  box-shadow: var(--sh-sm);
  overflow: hidden;
}

.tabs {
  display: flex;
  gap: var(--sp-2);
  padding: var(--sp-4);
  border-bottom: 1px solid var(--c-line);
  background: var(--c-mist);
}

.tab {
  border: none;
  background: transparent;
  font-family: var(--ff-body);
  font-size: var(--fs-sm);
  color: var(--c-muted);
  padding: var(--sp-2) var(--sp-4);
  border-radius: var(--r-full);
  cursor: pointer;
  transition:
    background 0.2s ease,
    color 0.2s ease;
}

.tab:hover {
  color: var(--c-teal-strong);
  background: var(--c-mint);
}

.tab--active {
  background: var(--c-teal);
  color: #fff;
}

.tab-panel {
  padding: var(--sp-6);
}
</style>
