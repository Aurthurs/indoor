import { supabase } from './supabase'

export async function queryUsers() {
  const { data, error } = await supabase.from('user').select('*')

  if (error) {
    console.error('查询失败:', error)
    return null
  }

  return data
}

queryUsers().then((users) => {
  console.log('用户列表:', users)
})
