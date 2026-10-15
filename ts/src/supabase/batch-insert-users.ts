import { supabase } from './supabase'

async function batchInsertUsers(count: number = 100) {
  const users = Array.from({ length: count }, (_, i) => ({
    user_name: `用户${i + 1}`,
    gender: i % 2 === 0 ? '男' : '女',
    created_at: new Date().toISOString()
  }))

  const { data, error } = await supabase.from('user').insert(users).select()

  if (error) {
    console.error('批量插入失败:', error)
    return
  }

  console.log(`成功插入 ${data?.length} 条数据`)
}

batchInsertUsers(100)
