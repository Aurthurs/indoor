<template>
  <div class="demo-panel">
    <p>父-子通信</p>
    <p>{{ msg }}</p>
  </div>
</template>

<script setup lang="ts">
const props = defineProps({
  msg: String,
})
</script>
