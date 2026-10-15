<template>
  <div class="demo-panel">
    <p>子-父通信</p>
    <button class="demo-btn" @click="sendMessage">向父组件发送消息</button>
    <button class="demo-btn" @click="reset">重置</button>
  </div>
</template>

<script setup lang="ts">
import { ref } from 'vue'

// 1. 定义事件
const emit = defineEmits<{
  (e: 'send-message', message: string): void
}>()

// 2. 触发事件，传递数据
const msg = ref('')
const sendMessage = () => {
  msg.value = '12'
  emit('send-message', msg.value)
}

const reset = () => {
  msg.value = ''
  emit('send-message', msg.value)
}
</script>
