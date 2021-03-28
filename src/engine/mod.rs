pub mod renderer;


pub struct Engine {
    render_size: [u32; 2],
    tick_rate: u32,
    frame_rate: u32,
}

impl Engine {
    pub fn new() -> Self {
        Engine {
            render_size: [1000, 1000],
            tick_rate: 128,
            frame_rate: 1000,
        }
    }

    pub fn run_loop(self){
        renderer::render();
    }
}