
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

    -- Check whether we've collided
    for i, v in ipairs(self.trail) do
      if v == self.pos then
        self:game_over()
        break
      end
    end

    -- Check whether OOB
    local win = Window.get_size()
    if self.pos.x >= win.x - 16 or self.pos.x < 16 or
      self.pos.y >= win.y - 16 or self.pos.y < 32 then
        self:game_over()
    end

  end
end

function SnakeHead:game_over()
  print("Final score: " .. self.score)
  Game:terminate()
end

function SnakeHead:key_down(k)
  if snake_head_keys[k] and (self.dir - snake_head_keys[k]) % (2 * math.pi) ~= math.pi then
    self.dir = snake_head_keys[k]
  end
end

function SnakeHead:draw()
  Canvas.set_color(Color(1, 1, 1))
  Canvas.draw_rectangle(self.pos, self.pos + Vector2(15, 15))
  for i = 0, self.trail_len - 1 do
    local alpha = i / (2 * self.trail_len) + 0.5
    Canvas.set_color(Color(1, 1, 1, alpha))
    local pos = self.trail[(self.trail_ptr + i) % self.trail_len]
    if pos then
      Canvas.draw_rectangle(pos, pos + Vector2(15, 15))
    end
  end
end

OuterWalls = Object:define()

function OuterWalls:draw()
  Canvas.set_color(Color(1, 1, 1))
  local win = Window.get_size()
  local ul, lr = Vector2(16, 32), win - Vector2(16, 16)
  local ll, ur = Vector2(16, win.y - 16), Vector2(win.x - 16, 32)
  Canvas.draw_line(ul, ur)
  Canvas.draw_line(ur, lr)
  Canvas.draw_line(lr, ll)
  Canvas.draw_line(ll, ul)
end

table.insert(Room.get_objects(), SnakeHead:new({x=128, y=128}))
table.insert(Room.get_objects(), OuterWalls:new())
