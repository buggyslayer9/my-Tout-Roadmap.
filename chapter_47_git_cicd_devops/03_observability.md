# 49.3 Observability and Telemetry

Building a system is only half the job. Once it is running in production, how do you know if it is working? If a user clicks a button on their phone, the request travels to the load balancer, into the Axum backend, queries the Postgres database, and returns. If it fails, where did it fail?

This requires **Observability**.

## The Three Pillars of Observability

1. **Logs:** Discrete records of events (e.g., "User 42 logged in at 10:00am").
2. **Metrics:** Aggregated numbers over time (e.g., "CPU is at 80%", "We are processing 500 requests per second").
3. **Traces:** A continuous tracking of a single request across multiple microservices.

## 1. Structured Logging in Rust (`tracing`)

Traditional `println!` is useless in production. It doesn't tell you the time, the thread, or the context.

In Rust, the industry standard is the `tracing` ecosystem. Instead of writing unstructured strings, you write structured events.

```rust
use tracing::{info, error, instrument};

// The #[instrument] macro automatically logs when this function starts,
// what arguments it received, and when it finishes!
#[instrument]
async fn process_payment(user_id: u32, amount: f64) -> Result<(), String> {
    info!(user_id, amount, "Starting payment processing"); // Structured logging
    
    if amount < 0.0 {
        error!(user_id, amount, "Invalid payment amount detected!");
        return Err("Invalid amount".to_string());
    }
    
    // Process payment...
    info!("Payment successful");
    Ok(())
}
```
*Output (when formatted as JSON for servers):*
`{"timestamp":"2026-03-14T10:00:00Z","level":"INFO","user_id":42,"amount":50.0,"message":"Starting payment processing","span":{"name":"process_payment"}}`

## 2. Metrics (Prometheus)

Logs tell you *what* happened, but searching 10 million logs to see your current CPU usage is slow. 

**Prometheus** is a time-series database. Your Rust app exposes an HTTP endpoint (e.g., `/metrics`). Prometheus pings it every 15 seconds to collect raw numbers.

```text
# Example Prometheus Metrics Output
http_requests_total{method="GET", route="/api/users"} 1054
database_query_duration_seconds_average 0.045
```

## 3. Visualization (Grafana)

Nobody wants to read JSON logs or raw metrics text. **Grafana** is an open-source dashboard tool that connects to Prometheus and your logs.

You build visual graphs:
- A dial showing current Memory Usage.
- A line chart showing HTTP 500 Error Rates over the last hour.
- Alerts that send a message to a Discord/Slack channel if the Database CPU hits 95%.

By combining **Docker**, **Axum**, **tracing**, **Prometheus**, and **Grafana**, you have built a true, enterprise-grade, Zero-To-Hero software architecture.
