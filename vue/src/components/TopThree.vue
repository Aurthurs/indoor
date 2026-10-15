<template>
  <div class="demo-panel">
    <p>Top Three</p>
    <input class="demo-input" type="text" v-model="count" />
  </div>
</template>

<script setup lang="ts">
import { ref, watch } from 'vue'

const props = defineProps<{
  count: number
}>()

const emit = defineEmits<{
  (e: 'update:count', val: number): void
}>()

const count = ref(props.count)

watch(count, (val) => {
  emit('update:count', val)
})
</script>
