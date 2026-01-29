// OrderedMap - HashMap-like structure that maintains insertion order
// Used to fix Bug #146: C translation non-determinism in loop variable naming
//
// Unlike std::collections::HashMap which has non-deterministic iteration order,
// OrderedMap preserves the order in which keys were inserted.

#![allow(dead_code)]

use std::hash::Hash;

#[derive(Debug, Clone)]
pub struct OrderedMap<K, V> {
    entries: Vec<(K, V)>,
}

impl<K: Eq + Hash + Clone, V: Clone> OrderedMap<K, V> {
    pub fn new() -> Self {
        OrderedMap { entries: Vec::new() }
    }

    pub fn insert(&mut self, key: K, value: V) -> Option<V> {
        // Check if key already exists
        for (existing_key, existing_value) in &mut self.entries {
            if existing_key == &key {
                let old_value = existing_value.clone();
                *existing_value = value;
                return Some(old_value);
            }
        }
        // Key doesn't exist, append to end
        self.entries.push((key, value));
        None
    }

    pub fn get(&self, key: &K) -> Option<&V> {
        for (existing_key, value) in &self.entries {
            if existing_key == key {
                return Some(value);
            }
        }
        None
    }

    pub fn get_mut(&mut self, key: &K) -> Option<&mut V> {
        for (existing_key, value) in &mut self.entries {
            if existing_key == key {
                return Some(value);
            }
        }
        None
    }

    pub fn contains_key(&self, key: &K) -> bool {
        self.get(key).is_some()
    }

    pub fn remove(&mut self, key: &K) -> Option<V> {
        let mut index = None;
        for (i, (existing_key, _)) in self.entries.iter().enumerate() {
            if existing_key == key {
                index = Some(i);
                break;
            }
        }
        if let Some(i) = index {
            let (_, value) = self.entries.remove(i);
            Some(value)
        } else {
            None
        }
    }

    pub fn len(&self) -> usize {
        self.entries.len()
    }

    pub fn is_empty(&self) -> bool {
        self.entries.is_empty()
    }

    pub fn iter(&self) -> impl Iterator<Item = (&K, &V)> {
        self.entries.iter().map(|(k, v)| (k, v))
    }

    pub fn iter_mut(&mut self) -> impl Iterator<Item = (&K, &mut V)> {
        self.entries.iter_mut().map(|(k, v)| (k as &K, v))
    }

    pub fn keys(&self) -> impl Iterator<Item = &K> {
        self.entries.iter().map(|(k, _)| k)
    }

    pub fn values(&self) -> impl Iterator<Item = &V> {
        self.entries.iter().map(|(_, v)| v)
    }

    pub fn values_mut(&mut self) -> impl Iterator<Item = &mut V> {
        self.entries.iter_mut().map(|(_, v)| v)
    }

    pub fn clear(&mut self) {
        self.entries.clear();
    }
}

impl<K: Eq + Hash + Clone, V: Clone> Default for OrderedMap<K, V> {
    fn default() -> Self {
        Self::new()
    }
}
