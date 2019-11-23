
math.randomseed(os.time())

SnakeHead = Object:define()

local snake_head_keys = {
  [Key.LEFT] = math.pi,
  [Key.of('a')] = math.pi,
  [Key.UP] = 3 * math.pi / 2,
  [Key.of('w')] = 3 * math.pi / 2,
  [Key.DOWN] = math.pi / 2,
  [Key.of('s')] = math.pi / 2,
  [Key.RIGHT] = 0,
  [Key.of('d')] = 0,
}

function SnakeHead:init(t)
  self.pos = Vector2(t.x, t.y)
  self.dir = 0
  self.mov_count = 15
  self.mov_timer = 0
  self.trail_len = 5
  self.trail = {}
  self.trail_ptr = 0
  self.score = 0
end

function SnakeHead:step()
  self.mov_timer = self.mov_timer + 1
  if self.mov_timer >= self.mov_count then
    self.mov_timer = 0
    self.trail[self.trail_ptr] = self.pos
    self.trail_ptr = (self.trail_ptr + 1) % self.trail_len
    self.pos = self.pos + Vector2(16, 0):rotated(self.dir)

    self.score = self.score + 1
    if self.score % 20 == 0 then
      if self.mov_count > 5 then
        self.mov_count = self.mov_count - 1
      end
      self.trail_len = self.trail_len + 1
    end

  end
end

function SnakeHead:key_down(k)
  if snake_head_keys[k] then
    self.dir = snake_head_keys[k]
  end
end

function SnakeHead:draw()
  --Canvas.set_color(Color(0, 0, 0))
  --Canvas.draw_primitive(Constant.QUADS,
  --                      {Vector2(0, 0), Vector2(500, 0), Vector2(500, 500), Vector2(0, 500)})
  Canvas.set_color(Color(1, 1, 1))
  Canvas.draw_primitive(Constant.QUADS, {
    self.pos, self.pos + Vector2(15, 0),
    self.pos + Vector2(15, 15), self.pos + Vector2(0, 15)
  })
  for i = 0, self.trail_len - 1 do
    local alpha = i / (2 * self.trail_len) + 0.5
    Canvas.set_color(Color(1, 1, 1, alpha))
    local pos = self.trail[(self.trail_ptr + i) % self.trail_len]
    if pos then
      Canvas.draw_primitive(Constant.QUADS, {
        pos, pos + Vector2(15, 0),
        pos + Vector2(15, 15), pos + Vector2(0, 15)
      })
    end
  end
end

table.insert(Room.get_objects(), SnakeHead:new({x=128, y=128}))
